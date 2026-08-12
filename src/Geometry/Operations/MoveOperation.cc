#include <Geometry/Operations/MoveOperation.h>

Geometry MoveOperation::do_operation() {
	Geometry new_geometry(this->input_geometry);

	std::vector<int> vertices_to_move = this->selection_as_vertices();
	for (int vertex_id : vertices_to_move) {
		Vertex& v = new_geometry.get_vertex(vertex_id);
		v.position += this->offset;
	}
	return new_geometry;
}