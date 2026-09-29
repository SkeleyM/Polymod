#include <Geometry/Operations/CreatePrimitiveOperation.h>
#include <Geometry/GeometryPrimitives.h>

Geometry CreatePrimitiveOperation::do_operation() {
	Geometry new_geometry(this->input_geometry);
	Geometry primitive_geometry;

	// Create the correct primitive geometry
	switch (this->primitive_type) {
	case(GeometryPrimitives::Cube): {
		primitive_geometry = GeometryPrimitives::create_primitive_cube(this->position, this->diameter);
		break;
	}
	case(GeometryPrimitives::Cylinder): {
		primitive_geometry = GeometryPrimitives::create_primitive_cylinder(this->position, this->diameter, this->iterations, this->height);
		break;
	}
	case(GeometryPrimitives::Sphere_Uv): {
		primitive_geometry = GeometryPrimitives::create_primitive_sphere_uv(this->position, this->diameter, this->segments, this->iterations);
		break;
	}
	case(GeometryPrimitives::Torus): {
		primitive_geometry = GeometryPrimitives::create_primitive_torus(this->position, this->hole, this->diameter, this->segments, this->iterations);
		break;
	}
	case(GeometryPrimitives::Circle): {
		primitive_geometry = GeometryPrimitives::create_primitive_circle(this->position, this->diameter, this->iterations);
		break;
	}
	case(GeometryPrimitives::Plane): {
		primitive_geometry = GeometryPrimitives::create_primitive_plane(this->position, this->diameter);
		break;
	}
	case(GeometryPrimitives::Vertex): {
		primitive_geometry.add_vertex(this->position);
		break;
	}
	}

	if (new_geometry.get_all_vertex_ids().size() == 0) {
		return primitive_geometry;
	}

	new_geometry.join({ primitive_geometry });
	return new_geometry;
}