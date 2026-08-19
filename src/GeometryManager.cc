#include <GeometryManager.h>

void GeometryManager::create_new_geometry(std::string name) {
	std::shared_ptr<Geometry> new_geometry = std::make_shared<Geometry>(name);
	this->geometry.push_back(new_geometry);
}

void GeometryManager::delete_geometry(std::string name) {
	for (int i = 0; i < this->geometry.size(); i++) {
		if (this->geometry[i].get()->name == name) {
			this->geometry.erase(this->geometry.begin() + i);
			return;
		}
	}
}

std::weak_ptr<Timeline> GeometryManager::get_timeline(std::weak_ptr<Geometry> geometry) {
	assert(!geometry.expired());

	// If the geometry does not have a timeline create one
	if (this->geometry_timelines.find(geometry.lock().get()->name) == this->geometry_timelines.end()) {
		this->geometry_timelines[geometry.lock().get()->name] = std::make_shared<Timeline>();
	}

	return this->geometry_timelines[geometry.lock().get()->name];
}

std::weak_ptr<Geometry> GeometryManager::get_geometry(std::string name) {
	for (auto geometry : this->geometry) {
		if (geometry.get()->name == name)
			return geometry;
	}
	abort();
}

std::vector<std::shared_ptr<Geometry>> GeometryManager::get_all_geometry() {
	return this->geometry;
}
