#pragma once

#include <GeometryManager.h>
#include <Geometry/GeometryPrimitives.h>

#include <string>

namespace PolymodProject {
	class ProjectManager {
	private:
		std::string name;
		GeometryManager geometry_manager;

	public:
		ProjectManager(std::string name) {
			this->name = name;

			// Add the geometry
			auto new_geo = this->geometry_manager.create_new_geometry("Cube");
			*new_geo.lock().get() = GeometryPrimitives::create_primitive_cube({ 0.0f, 0.0f, 0.0f }, 1.0f);
			new_geo.lock().get()->calculate_normals(SHADE_FLAT);
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
