#include <Geometry/Operations/ExtrudeOperation.h>

Geometry ExtrudeOperation::do_operation() {
	Geometry new_geometry(this->input_geometry);

	if (this->selection.selected_vertices.has_value()) {
		std::vector<int> affected_vertices;

		for (auto vert : *this->selection.selected_vertices) {
			int new_vert;
		
			// Get current position
			Vertex v = new_geometry.get_vertex(vert);
			// Add new vertex
			int e_v_id = new_geometry.add_vertex(v.position + this->extrusion);
			// Connect to current
			new_geometry.add_connection(vert, e_v_id);

			affected_vertices.push_back(e_v_id);
		}
	}
	else if (this->selection.selected_edges.has_value()) {
		std::vector<std::pair<int, int>> affected_edges;

		auto edges = *this->selection.selected_edges;
		for (auto edge : edges) {
			// Get edge positions
			Vertex v1 = new_geometry.get_vertex(edge.first);
			Vertex v2 = new_geometry.get_vertex(edge.second);

			// Add new pair
			int e_v1_id = new_geometry.add_vertex(v1.position + this->extrusion);
			int e_v2_id = new_geometry.add_vertex(v2.position + this->extrusion);

			// Connect the new pair 
			new_geometry.add_connection(e_v1_id, e_v2_id);
			new_geometry.add_connection(e_v1_id, edge.first);
			new_geometry.add_connection(e_v2_id, edge.second);
			new_geometry.define_face({ edge.first, edge.second, e_v2_id, e_v1_id });

			affected_edges.push_back({ e_v1_id , e_v2_id });
		}
		this->affected_edges = affected_edges;
	}
	else if (this->selection.selected_faces.has_value()) {
		auto faces = *this->selection.selected_faces;
		for (Face face : faces) {
			int vertex_count = face.vertices.size();

			std::vector<int> new_vertex_ids;

			for (int vertex_id : face.vertices) {
				// Create a new vertex and extrude it
				Vertex vertex = new_geometry.get_vertex(vertex_id);
				int new_vertex_id = new_geometry.add_vertex(vertex.position + extrusion);
				new_vertex_ids.push_back(new_vertex_id);
			}

			// Connect all the edges
			for (int v = 0; v < new_vertex_ids.size()-1; v++) {
				new_geometry.add_connection(
					new_vertex_ids[v], 
					new_vertex_ids[v+1]
				);
			}
			// Connect first to the last
			new_geometry.add_connection(0, new_vertex_ids.size() - 1);

			// Connect the new extruded face vertices to the original vertices
			for (int v = 0; v < new_vertex_ids.size(); v++) {
				new_geometry.add_connection(
					new_vertex_ids[v],
					face.vertices[v]
				);
			}

			// Define the new faces
			for (int v = 0; v < new_vertex_ids.size()-1; v++) {
				new_geometry.define_face(
					{
						new_vertex_ids[v],
						new_vertex_ids[v + 1],
						face.vertices[v],
						face.vertices[v + 1]
					}
				);
			}
			new_geometry.define_face(
				{
					new_vertex_ids[0],
					new_vertex_ids[new_vertex_ids.size()-1],
					face.vertices[0],
					face.vertices[new_vertex_ids.size() - 1]
				}
			);

			// Define the extruded face
			new_geometry.define_face(new_vertex_ids);
		}
	}

	return new_geometry;
}
