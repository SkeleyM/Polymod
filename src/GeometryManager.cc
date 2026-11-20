#include <GeometryManager.h>
#include <Engine.h>

GeometryManager::~GeometryManager() {
	// Ensure all meshes are deleted since their geometry will be.
	auto& scene = Engine::get_instance()->get_active_scene();
	for (auto& [s, m] : this->geometry_meshes) {
		scene.remove_mesh(m);
	}
}

std::weak_ptr<Geometry> GeometryManager::create_new_geometry(std::string name) {
	std::shared_ptr<Geometry> new_geometry = std::make_shared<Geometry>(name);
	this->geometry.push_back(new_geometry);
	return new_geometry;
}

void GeometryManager::delete_geometry(std::string name) {
	for (int i = 0; i < this->geometry.size(); i++) {
		if (this->geometry[i].get()->name == name) {
			this->geometry.erase(this->geometry.begin() + i);
			return;
		}
	}
}

void GeometryManager::update_geometry_mesh(std::string name) {
	auto target_geometry_option = this->get_geometry(name);
	// If the geometry does not exist, nothing to be done
	if (!target_geometry_option.has_value()) {
		return;
	}

	Engine* engine = Engine::get_instance();
	auto& scene = engine->get_active_scene();
	auto& target_geometry = target_geometry_option.value();

	// If the geometry already has a mesh remove it so it can be replaced
	if (this->geometry_meshes.find(name) != this->geometry_meshes.end()) {
		// Delete the mesh from the scene and create a new one
		scene.remove_mesh(this->geometry_meshes[name]);
	}

	// Add new mesh to scene
	auto new_mesh = std::make_shared<Mesh>(target_geometry.lock().get()->triangulate());
	this->geometry_meshes[name] = new_mesh;
	scene.add_mesh(new_mesh);
}

std::shared_ptr<Mesh> GeometryManager::get_geometry_mesh(std::string name) {
	if (this->geometry_meshes.find(name) == this->geometry_meshes.end()) {
		return nullptr;
	}

	return this->geometry_meshes[name];
}

std::weak_ptr<Timeline> GeometryManager::get_timeline(std::weak_ptr<Geometry> geometry) {
	assert(!geometry.expired());

	// If the geometry does not have a timeline create one
	if (this->geometry_timelines.find(geometry.lock().get()->name) == this->geometry_timelines.end()) {
		this->geometry_timelines[geometry.lock().get()->name] = std::make_shared<Timeline>();
	}

	return this->geometry_timelines[geometry.lock().get()->name];
}

std::optional<std::weak_ptr<Geometry>> GeometryManager::get_geometry(std::string name) {
	for (auto geometry : this->geometry) {
		if (geometry.get()->name == name)
			return geometry;
	}
	return std::nullopt;
}

std::vector<std::shared_ptr<Geometry>> GeometryManager::get_all_geometry() {
	return this->geometry;
}
