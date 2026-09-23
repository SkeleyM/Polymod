#pragma once

#include <Geometry/Geometry.h>

#include <vector>
#include <optional>

namespace GeometryRaycasting {
	std::optional<Face> raycast_face(Geometry& geometry, Vector3 ray_origin, Vector3 ray_direction);
	std::optional<std::pair<int, int>> raycast_edge(Geometry& geometry, Vector3 ray_origin, Vector3 ray_direction);
	std::optional<int> raycast_vertex(Geometry& geometry, Vector3 ray_origin, Vector3 ray_direction);
};