#include <Geometry/Operations/VertexSpinOperation.h>

std::vector<int> spin_vertex(Geometry& geometry, int vertex_id, Vector3 origin, int samples, float angle_x, float angle_y) {
	std::vector<int> new_vertex_ids;
	new_vertex_ids.reserve(samples);

	for (int s = 1; s < samples + 1; s++) {
		Vertex& vertex = geometry.get_vertex(vertex_id);

		Vector3 origin_offset = Vector3(origin.x, vertex.position.y, origin.z);

		float radius = fabs(glm::length(vertex.position - origin_offset));

		float new_angle_x = (angle_x / samples) * s;
		float new_angle_y = (angle_y / samples) * s;
		Vector3 vertex_position = Vector3(
			radius * sin(glm::radians(new_angle_x)),
			0,
			radius * cos(glm::radians(new_angle_x))
		) + Vector3(0, vertex.position.y, 0);

		// Add the new vertex
		int id = geometry.add_vertex(vertex_position + origin);
		new_vertex_ids.push_back(id);
	}

	// Connect new vertices in a loop
	for (int v = 0; v < samples-1; v++) {
		geometry.add_connection(new_vertex_ids[v], new_vertex_ids[v + 1]);
	}
	geometry.add_connection(new_vertex_ids[0], new_vertex_ids[samples-1]);

	return new_vertex_ids;
}

Geometry VertexSpinOperation::do_operation() {
	Geometry new_geometry(this->input_geometry);

	if (this->samples == 0) 
		return new_geometry;

	if (this->selection.selected_faces.has_value()) {
		std::vector<Face> faces = *this->selection.selected_faces;

		std::vector <std::vector<int>> new_ids;
		Face face = faces[0];

		for (int vertex_id : face.vertices) {
			std::vector<int> ids = spin_vertex(new_geometry, vertex_id, this->origin, this->samples, this->angle_x, this->angle_y);
			new_ids.push_back(ids);
		}

		// Create connections between each of the samples
		for (int s = 0; s < new_ids.size(); s++) {
			for (int v = 0; v < samples; v++) {
				new_geometry.add_connection(new_ids[s % new_ids.size()][v], new_ids[(s + 1) % new_ids.size()][v]);
			}
		}

		for (int new_id_index = 0; new_id_index < new_ids.size(); new_id_index++) {
			// loop through the new ids and create connections between them
			for (int sample = 0; sample < samples; sample++) {
				// The modulus operator allows wrapping around the new ids and samples to create 
				// the face between the first and last of the new ids
				new_geometry.define_face({
					new_ids[new_id_index % new_ids.size()][sample % samples],
					new_ids[(new_id_index + 1) % new_ids.size()][sample % samples],
					new_ids[new_id_index % new_ids.size()][(sample + 1) % samples],
					new_ids[(new_id_index + 1) % new_ids.size()][(sample + 1) % samples] });
			}
		}

		// Set affected vertices
		this->affected_vertices = std::vector<int>();
		for (auto v : new_ids) {
			this->affected_vertices.value().insert(this->affected_vertices.value().end(), v.begin(), v.end());
		}
	}

	return new_geometry;
}