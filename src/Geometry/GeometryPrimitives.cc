#include <Geometry/GeometryPrimitives.h>

#include <Geometry/Operations/ExtrudeOperation.h>
#include <Geometry/Operations/MoveOperation.h>
#include <Geometry/Operations/VertexSpinOperation.h>

Geometry GeometryPrimitives::create_primitive_cube(Vector3 position, float diameter) {
	Geometry geometry = GeometryPrimitives::create_primitive_plane(Vector3(0.0f, 0.0f, -(diameter / 2)), diameter);
	geometry.name = "Cube";

	// extrude by the diameter
	// This will give a cube centered around the origin.
	SelectedGeometry selection;
	selection.selected_faces = geometry.get_faces();
	ExtrudeOperation extrude(geometry, selection, Vector3(0.0f, 0.0f, diameter));
	geometry = extrude.do_operation();

	MoveOperation move_to_position(geometry, {}, position);
	return move_to_position.do_operation();
}

Geometry GeometryPrimitives::create_primitive_cylinder(Vector3 position, float diameter, int iterations, float height) {
	Geometry geometry = create_primitive_circle(position, diameter, iterations);
	geometry.name = "Cylinder";

	SelectedGeometry selection;
	selection.selected_faces = { geometry.get_faces() };
	ExtrudeOperation extrude(geometry, selection, Vector3(0.0f, height, 0.0f));
	geometry = extrude.do_operation();

	MoveOperation move(geometry, {}, Vector3(0.0f, -(height/2), 0.0f));

	return move.do_operation();
}

Geometry GeometryPrimitives::create_primitive_sphere_uv(Vector3 position, float diameter, int iterations) {
	return Geometry("Uv_Sphere");
}

Geometry GeometryPrimitives::create_primitive_torus(Vector3 position, float diameter, int iterations) {
	return Geometry("Torus");
}

Geometry GeometryPrimitives::create_primitive_circle(Vector3 position, float diameter, int iterations) {
	Geometry geometry("Circle");
	geometry.add_vertex(Vector3(0.0f, 0.0f, diameter / 2));
	
	SelectedGeometry selection;
	selection.selected_vertices = { 0 };
	VertexSpinOperation spin(geometry, selection, { 0.0f, 0.0f, 0.0f }, iterations, 360.0f, 0.0f);

	geometry = spin.do_operation();
	std::vector<int> ids;
	for (int i = 1; i <= iterations; i++)
		ids.push_back(i);
	geometry.define_face(ids);

	return geometry;
}

Geometry GeometryPrimitives::create_primitive_plane(Vector3 position, float diameter) {
	Geometry geometry("Plane");

	geometry.add_vertex((Vector3(-0.5f, -0.5f, 0.0f) * diameter) + position);
	geometry.add_vertex((Vector3(-0.5f, 0.5f, 0.0f) * diameter) + position);
	geometry.add_vertex((Vector3(0.5f, 0.5f, 0.0f) * diameter) + position);
	geometry.add_vertex((Vector3(0.5f, -0.5f, 0.0f) * diameter) + position);

	geometry.add_connection(0, 1);
	geometry.add_connection(1, 2);
	geometry.add_connection(2, 3);
	geometry.add_connection(3, 0);

	geometry.define_face({ 0, 1, 2, 3 });

	return geometry;
}
