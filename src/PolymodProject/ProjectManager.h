#pragma once

#include <GeometryManager.h>
#include <Geometry/GeometryPrimitives.h>

#include <string>
#include <filesystem>

namespace Polymodel::Project {
	class ProjectManager {
	private:
		std::string name;
		std::filesystem::path path;
		GeometryManager geometry_manager;

	public:
		ProjectManager(std::filesystem::path path, std::string name) : path(path), name(name) {}

		std::string get_project_name() {
			return this->name;
		}

		void set_project_name(std::string name) {
			this->name = name;
		}

		GeometryManager& get_geometry_manager() {
			return this->geometry_manager;
		}

		std::filesystem::path get_project_path() {
			return this->path;
		}

		void set_project_path(std::filesystem::path path) {
			this->path = path;
		}
	};
}
