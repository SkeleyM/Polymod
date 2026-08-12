#include <Geometry/Operations/ScaleOperation.h>

Geometry ScaleOperation::do_operation() {
	Geometry new_geometry(input_geometry);

	std::vector<int> vertices = this->selection_as_vertices();

	// If the selection is blank then that means that we should scale the entire geometry.
	if (!selection.selected_edges.has_value() && !selection.selected_faces.has_value() && !selection.selected_vertices.has_value()) {
		vertices = new_geometry.get_all_vertex_ids();
	}

	// Compute the center of the selected vertices
	Vector3 center = Vector3(0.0f, 0.0f, 0.0f);
	for (int vertex_index : vertices) {
		center += new_geometry.get_vertex(vertex_index).position;
	}
	center /= (float)vertices.size();
	
	// Calculate the distance from the world origin to the center of the selected vertices
	for (int vertex_index : vertices) {
		Vertex& vertex = new_geometry.get_vertex(vertex_index);
		vertex.position = (vertex.position - center) * scale;
		vertex.position += center;
	}


	return new_geometry;
}