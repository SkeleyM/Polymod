#pragma once

#include <string>
#include <vector>
#include <optional>
#include <Geometry/Geometry.h>

namespace GeometryPrimitives {
	Geometry create_primitive_cube(Vector3 position, float diameter);
	Geometry create_primitive_cylinder(Vector3 position, float diameter, int iterations, float height);
	Geometry create_primitive_sphere_uv(Vector3 position, float diameter, int iterations);
	Geometry create_primitive_torus(Vector3 position, float diameter, int iterations);
	Geometry create_primitive_circle(Vector3 position, float diameter, int iterations);
	Geometry create_primitive_plane(Vector3 position, float diameter);
}