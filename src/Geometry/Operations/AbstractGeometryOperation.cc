#include <set>

#include <Geometry/Operations/AbstractGeometryOperation.h>

std::vector<int> AbstractGeometryOperation::selection_as_vertices() {
	std::set<int> vertices = std::set<int>();

	// If there is nothing selected, affect all vertices;
	if (!this->selection.selected_vertices.has_value()
		&& !this->selection.selected_edges.has_value()
		&& !this->selection.selected_faces.has_value()) {
		return this->input_geometry.get_all_vertex_ids();
	}

	if (this->selection.selected_vertices.has_value()) {
		for (int v : this->selection.selected_vertices.value()) {
			vertices.insert(v);
		}
	}

	if (this->selection.selected_edges.has_value()) {
		for (std::pair<int, int> edge : this->selection.selected_edges.value()) {
			vertices.insert(edge.first);
			vertices.insert(edge.second);
		}
	}

	if (this->selection.selected_faces.has_value()) {
		for (Face face : this->selection.selected_faces.value()) {
			for (int v : face.vertices) {
				vertices.insert(v);
			}
		}
	}

	return std::vector<int>(vertices.begin(), vertices.end());
}