#include <Geometry/Operations/RotateOperation.h>

Geometry RotateOperation::do_operation() {
	Geometry new_geometry(this->input_geometry);

	// No selection so we rotate the entire geometry
	if (!this->selection.selected_vertices.has_value() &&
		!this->selection.selected_edges.has_value() &&
		!this->selection.selected_faces.has_value()) {
		// Just change the transform. as its more efficient than rotating all the vertices.
	
		new_geometry.transform.set_rotation_euler(this->axis * this->angle);
		return new_geometry;
	}

	std::vector<int> vertices = this->selection_as_vertices();
	for (int v = 0; v < vertices.size(); v++) {
		Vertex& vertex = new_geometry.get_vertex(vertices[v]);
		vertex.position = Vector4(vertex.position, 1.0f) * glm::rotate(glm::mat4(1.0f), this->angle, this->axis);
	}
	return new_geometry;
}