#include <PolymodProject/ProjectManager.h>

#include <PolymodProject/PolymodProject.h>
#include <Geometry/Formats/GeometryFormats.h>

#include <nlohmann/json.hpp>

#include <fstream>
#include <string>

bool Polymodel::Project::export_project(std::filesystem::path project_path, std::weak_ptr<Polymodel::Project::ProjectManager> project) {
	auto& manager = project.lock()->get_geometry_manager();

	std::filesystem::create_directories(project_path);

	Polymodel::Project::ProjectMetadata metadata;
	metadata.last_accessed = std::time(0);

	Polymodel::Project::save_metadata(project_path, metadata);
	Polymodel::Project::export_geometry(project_path, manager);

	return true;
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


std::shared_ptr<Polymodel::Project::ProjectManager> Polymodel::Project::import_project(std::filesystem::path project_path) {
	// Set project name to the end of the path, which is the name of the project folder
	auto project_name = project_path.filename().string();
	std::shared_ptr<Polymodel::Project::ProjectManager> project = std::make_shared<Polymodel::Project::ProjectManager>(project_name);

	if (!std::filesystem::exists(project_path))
		return nullptr;

	Polymodel::Project::import_geometry(project_path, project->get_geometry_manager());

	return project;
}

bool Polymodel::Project::import_geometry(std::filesystem::path project_path, GeometryManager& manager) {
	auto geometry_path = project_path / "Geometry";
	if (!std::filesystem::exists(geometry_path))
		return false;

	auto spec = GeometryFormat::GeometryFormatSpec();
	auto format_fac = GeometryFormat::GeometryFormatFactory();
	auto format = format_fac.create_format(spec);

	for (auto& entry : std::filesystem::directory_iterator(geometry_path)) {
		if (entry.is_directory()) continue;
		auto value = GeometryFormat::GeometryFileHandler::import_geometry(format.get(), entry);

		// Only add to manager if successfully imported
		if (value.has_value()) {
			auto new_geo = manager.create_new_geometry("Placeholder");
			*new_geo.lock() = value.value();
			new_geo.lock()->name = entry.path().filename().string();
		}
			
	}

	return false;
}

Polymodel::Project::ProjectMetadata Polymodel::Project::read_metadata(std::filesystem::path project_path) {
	abort();
	return {};
}

void Polymodel::Project::save_metadata(std::filesystem::path project_path, Polymodel::Project::ProjectMetadata metadata) {
	using namespace nlohmann::literals;
	nlohmann::json json = {
		{"last_accessed", metadata.last_accessed}
	};

	std::ofstream file(project_path / "metadata.json", std::ios::out);
	file << json;
}
