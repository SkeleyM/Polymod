#pragma once
#include <Geometry/Geometry.h>
#include <Geometry/Timeline.h>

#include <vector>
#include <string>
#include <memory>
#include <map>

class GeometryManager {
private:
	std::vector<std::shared_ptr<Geometry>> geometry;
	std::unordered_map<std::string, std::shared_ptr<Timeline>> geometry_timelines;
public:
	void create_new_geometry(std::string name);
	void delete_geometry(std::string name);
	std::weak_ptr<Timeline> get_timeline(std::weak_ptr<Geometry> geometry);
	std::weak_ptr<Geometry> get_geometry(std::string name);
	std::vector<std::shared_ptr<Geometry>> get_all_geometry();
};