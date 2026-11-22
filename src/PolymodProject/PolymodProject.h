#pragma once

#include <GeometryManager.h>
#include <filesystem>
#include <string.h>

namespace Polymodel::Project {
	struct ProjectMetadata {
		uint64_t last_accessed;
	};

	bool export_project(std::weak_ptr<Polymodel::Project::ProjectManager> project);
	std::shared_ptr<Polymodel::Project::ProjectManager> import_project(std::filesystem::path project_path);

	ProjectMetadata read_metadata(std::filesystem::path project_path);
	void save_metadata(std::filesystem::path project_path, ProjectMetadata metadata);

	bool export_geometry(std::filesystem::path project_path, GeometryManager& manager);
	bool import_geometry(std::filesystem::path project_path, GeometryManager& manager);


	std::string export_reference_transforms(std::vector<std::pair<std::string, Transform>> transforms);
	std::vector<std::pair<std::string, Transform>> import_reference_transforms(std::string serialised_transforms);
	void export_references(std::filesystem::path, ReferenceImageManager& image_manager);
	void import_references(std::filesystem::path, ReferenceImageManager& image_manager);
}