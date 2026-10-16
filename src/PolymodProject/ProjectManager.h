#pragma once

#include <GeometryManager.h>
#include <Geometry/GeometryPrimitives.h>

#include <string>

namespace Polymodel::Project {
	class ProjectManager {
	private:
		std::string name;
		GeometryManager geometry_manager;

	public:
		ProjectManager(std::string name) {
			this->name = name;
		}

		std::string get_project_name() {
			return this->name;
		}

		void set_project_name(std::string name) {
			this->name = name;
		}

		GeometryManager& get_geometry_manager() {
			return this->geometry_manager;
		}
	};
}
