#pragma once

#include <GeometryManager.h>
#include <filesystem>
#include <string.h>

namespace PolymodProject {
	struct ProjectMetadata {
		uint64_t last_accessed;
	};

	bool export_project(std::filesystem::path project_path, GeometryManager& manager);
	bool import_project(std::filesystem::path project_path, GeometryManager& manager);

	bool export_geometry(std::filesystem::path project_path, GeometryManager& manager);
	bool import_geometry(std::filesystem::path project_path, GeometryManager& manager);

	ProjectMetadata read_metadata(std::filesystem::path project_path);
	void save_metadata(std::filesystem::path project_path, ProjectMetadata metadata);
}