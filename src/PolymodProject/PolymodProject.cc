#include <PolymodProject/PolymodProject.h>
#include <Geometry/Formats/GeometryFormats.h>

#include <nlohmann/json.hpp>

#include <fstream>

bool PolymodProject::export_project(std::filesystem::path path, GeometryManager& manager) {
	std::filesystem::create_directories(path);

	PolymodProject::ProjectMetadata metadata;
	metadata.last_accessed = std::time(0);

	PolymodProject::save_metadata(path, metadata);
	PolymodProject::export_geometry(path, manager);

	return true;
}

bool PolymodProject::export_geometry(std::filesystem::path project_path, GeometryManager& manager) {
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


bool PolymodProject::import_project(std::filesystem::path project_path, GeometryManager& manager) {
	if (!std::filesystem::exists(project_path))
		return false;

	PolymodProject::import_geometry(project_path, manager);

	return false;
}

bool PolymodProject::import_geometry(std::filesystem::path project_path, GeometryManager& manager) {
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

PolymodProject::ProjectMetadata PolymodProject::read_metadata(std::filesystem::path project_path) {
	abort();
	return {};
}

void PolymodProject::save_metadata(std::filesystem::path project_path, PolymodProject::ProjectMetadata metadata) {
	using namespace nlohmann::literals;
	nlohmann::json json = {
		{"last_accessed", metadata.last_accessed}
	};

	std::ofstream file(project_path / "metadata.json", std::ios::out);
	file << json;
}
