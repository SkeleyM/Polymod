#include <PolymodProject/ProjectManager.h>

#include <PolymodProject/PolymodProject.h>
#include <Geometry/Formats/GeometryFormats.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>
#include <sstream>

bool Polymodel::Project::export_project(std::weak_ptr<Polymodel::Project::ProjectManager> project) {
	auto& manager = project.lock()->get_geometry_manager();
	auto& image_manager = project.lock()->get_reference_image_manager();
	auto project_path = project.lock()->get_project_path();

	std::filesystem::create_directories(project_path);

	Polymodel::Project::ProjectMetadata metadata;
	metadata.last_accessed = std::time(0);

	Polymodel::Project::save_metadata(project_path, metadata);
	Polymodel::Project::export_geometry(project_path, manager);
	Polymodel::Project::export_references(project_path, image_manager);

	return true;
}

std::shared_ptr<Polymodel::Project::ProjectManager> Polymodel::Project::import_project(std::filesystem::path project_path) {
	// Set project name to the end of the path, which is the name of the project folder
	auto project_name = project_path.filename().string();
	std::shared_ptr<Polymodel::Project::ProjectManager> project = std::make_shared<Polymodel::Project::ProjectManager>(project_path, project_name);

	if (!std::filesystem::exists(project_path))
		return nullptr;

	Polymodel::Project::import_geometry(project_path, project->get_geometry_manager());
	Polymodel::Project::import_references(project_path, project->get_reference_image_manager());

	return project;
}

Polymodel::Project::ProjectMetadata Polymodel::Project::read_metadata(std::filesystem::path project_path) {
	auto metadata_path = project_path / "metadata.json";
	std::ifstream data_file(metadata_path);
	std::stringstream data;
	data << data_file.rdbuf();
	std::string data_string = data.str();

	auto data_json = nlohmann::json::parse(data_string);

	Polymodel::Project::ProjectMetadata metadata;
	metadata.last_accessed = data_json["last_accessed"];

	return metadata;
}

void Polymodel::Project::save_metadata(std::filesystem::path project_path, Polymodel::Project::ProjectMetadata metadata) {
	nlohmann::json json = {
		{"last_accessed", metadata.last_accessed}
	};

	std::ofstream file(project_path / "metadata.json", std::ios::out);
	file << json;
}


bool Polymodel::Project::export_geometry(std::filesystem::path project_path, GeometryManager& manager) {
	auto geometry_path = project_path / "Geometry";
	std::filesystem::create_directory(geometry_path);

	// Create format
	auto spec = GeometryFormat::GeometryFormatSpec();
	auto format_fac = GeometryFormat::GeometryFormatFactory();
	auto format = format_fac.create_format(spec);

	bool did_export_fail = false;
	for (auto& geometry : manager.get_all_geometry()) {
		auto path = geometry_path / geometry.get()->name;
		if (!GeometryFormat::GeometryFileHandler::export_geometry(format.get(), *geometry.get(), path))
			did_export_fail = true;
	}

	return did_export_fail;
}

bool Polymodel::Project::import_geometry(std::filesystem::path project_path, GeometryManager& manager) {
	auto geometry_path = project_path / "Geometry";
	if (!std::filesystem::exists(geometry_path))
		return false;

	auto spec = GeometryFormat::GeometryFormatSpec();
	auto format_fac = GeometryFormat::GeometryFormatFactory();
	auto format = format_fac.create_format(spec);

	for (auto& entry : std::filesystem::directory_iterator(geometry_path)) {
		// Skip over rogue directories
		if (entry.is_directory()) continue;

		// Import obj file
		auto value = GeometryFormat::GeometryFileHandler::import_geometry(format.get(), entry);

		// Only add to manager if successfully imported
		if (value.has_value()) {
			auto new_geo = manager.create_new_geometry("Placeholder");
			*new_geo.lock() = value.value();
			new_geo.lock()->name = entry.path().filename().string();

			// Update it so that it appears initially in the scene
			manager.update_geometry_mesh(new_geo.lock()->name);
		}
	}

	return false;
}

// Export transform helper
static inline nlohmann::json export_transform_json(Transform& transform) {
	auto euler_rotation = transform.get_rotation_euler();
	nlohmann::json transform_json = {
		{
			"position", {
				transform.position.x, transform.position.y, transform.position.z
			}
		},
		{
			"rotation", {
				euler_rotation.x, euler_rotation.y, euler_rotation.z
			}
		},
		{
			"scale", {
				transform.scale.x, transform.scale.y, transform.scale.z
			}
		}
	};

	return transform_json;
}

// Import transform helper
static inline Transform import_transform_json(nlohmann::json json_transform) {
	Transform transform;

	auto& position_j = json_transform["position"];
	Vector3 position = Vector3(position_j[0], position_j[1], position_j[2]);

	auto& rotation_euler_j = json_transform["rotation"];
	Vector3 rotation = Vector3(rotation_euler_j[0], rotation_euler_j[1], rotation_euler_j[2]);

	auto& scale_j = json_transform["scale"];
	Vector3 scale = Vector3(scale_j[0], scale_j[1], scale_j[2]);

	transform.set_position(position);
	transform.set_rotation_euler(rotation);
	transform.set_scale(scale);

	return transform;
}

std::string Polymodel::Project::export_reference_transforms(std::vector<std::pair<std::string, Transform>> transforms) {
	nlohmann::json reference_transform_json;

	for (auto& transform_pair : transforms) {
		reference_transform_json[transform_pair.first] = export_transform_json(transform_pair.second);
	}

	return reference_transform_json.dump();
}

std::vector<std::pair<std::string, Transform>> Polymodel::Project::import_reference_transforms(std::string serialised_transforms) {
	std::vector<std::pair<std::string, Transform>> transforms;
	
	nlohmann::json reference_transform_json = nlohmann::json::parse(serialised_transforms);
	for (auto& [name, transform_json] : reference_transform_json.items()) {
		Transform transform = import_transform_json(transform_json);
		transforms.push_back({ name, transform });
	}

	return transforms;
}

void Polymodel::Project::export_references(std::filesystem::path project_path, ReferenceImageManager& image_manager) {
	auto references_path = project_path / "References";
	std::filesystem::create_directories(references_path);

	auto& images = image_manager.get_reference_images();

	// Create transform pairs and serialise them
	std::vector<std::pair<std::string, Transform>> transforms;
	for (auto& image : images) {
		transforms.push_back({ image.get()->name, image.get()->mesh->transform });
	}

	// Save transforms of all images in a sidecar json file
	std::ofstream transform_sidecar(references_path / "transforms.json", std::ios::out);
	transform_sidecar << Polymodel::Project::export_reference_transforms(transforms);

	// Export all reference images as png
	for (auto& image : images) {
		auto image_path = references_path / image.get()->name;
		std::ofstream image_file(image_path, std::ios::out | std::ios::binary);
		image_file.clear();
		auto bytes = Image2d::to_png_bytes(image->image);
		image_file.write((char*)(bytes.data()), bytes.size());
	}
}

void Polymodel::Project::import_references(std::filesystem::path project_path, ReferenceImageManager& image_manager) {
	auto references_path = project_path / "References";

	// If the references path doesnt exist then return
	if (!std::filesystem::exists(references_path))
		return;

	// Read in the sidecar file
	std::ifstream transform_sidecar(references_path / "transforms.json");
	std::stringstream transform_data;
	transform_data << transform_sidecar.rdbuf();
	// Parse the transform data
	std::vector<std::pair<std::string, Transform>> transforms = import_reference_transforms(transform_data.str());

	// use the names from the transforms file to import the reference images and set their transforms
	for (auto& [name, transform] : transforms) {
		std::filesystem::path image_file_path(references_path / name);
		// If it doesnt exist, just ignore it
		if (!std::filesystem::exists(image_file_path)) {
			continue;
		}

		auto reference_image = image_manager.create_reference_image(name, image_file_path);
		reference_image->mesh->transform = transform;
	}
}
