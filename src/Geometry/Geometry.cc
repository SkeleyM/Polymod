#include <Geometry/Geometry.h>


Geometry::Geometry(std::string name) {
	this->name = name;
	this->connections.reserve(100);
}

void Geometry::calculate_face_normals(int face_index, GeometryShadingType shading_type) {
	Face& face = this->faces[face_index];
	face.shading_type = shading_type;
	if (shading_type == SHADE_FLAT) {
		for (int v = 0; v < this->faces[face_index].vertices.size(); v++) {
			int vertex_id = face.vertices[v];
			Vector3 normal_vector = Vector3(0.0f);
			auto neighbours = this->get_neighbours(face.vertices[v]);
			for (int n = 0; n < neighbours.size(); n++) {
				if (std::find(face.vertices.begin(), face.vertices.end(), neighbours[n]) == face.vertices.end()) {
					Vector3 current_vertex_pos = this->get_vertex(vertex_id).position;
					Vector3 edge_vertex_pos = this->get_vertex(neighbours[n]).position;
					Vector3 edge_vector = edge_vertex_pos - current_vertex_pos;
					normal_vector += edge_vector;
				}
			}
			//this->get_vertex(vertex_id).normal = glm::normalize(normal_vector);
			face.face_normal = -glm::normalize(normal_vector);
		}
	}
	else if (shading_type == SHADE_SMOOTH) {
		for (int v = 0; v < this->faces[face_index].vertices.size(); v++) {
			int vertex_id = face.vertices[v];
			Vector3 normal_vector = Vector3(0.0f);
			auto neighbours = this->get_neighbours(face.vertices[v]);
			for (int n = 0; n < neighbours.size(); n++) {
					Vector3 current_vertex_pos = this->get_vertex(vertex_id).position;
					Vector3 edge_vertex_pos = this->get_vertex(neighbours[n]).position;
					Vector3 edge_vector = edge_vertex_pos - current_vertex_pos;
					normal_vector += edge_vector;
			}

			this->get_vertex(vertex_id).normal = -glm::normalize(normal_vector);
		}
	}
}

int Geometry::add_vertex(Vector3 vertex) {
	Vertex vert = Vertex(vertex, Vector3(0.3));
	this->vertices.push_back(vert);
	this->connections.push_back(std::vector<int>());
	return this->vertices.size() - 1;
}

Vertex& Geometry::get_vertex(int v_id) {
	return this->vertices[v_id];
}

std::vector<int> Geometry::get_all_vertex_ids() {
	std::vector<int> ids;
	ids.reserve(this->vertices.size());
	for (int v = 0; v < this->vertices.size(); v++) {
		ids.push_back(v);
	}
	return ids;
}

std::vector<Face>& Geometry::get_faces() {
	return this->faces;
}

void Geometry::add_connection(int v1, int v2) {
	// Check if the connection already exists
	// only need to check one, since the graph is biderectional
	if (std::find(this->connections[v1].begin(), this->connections[v1].end(), v2) != this->connections[v1].end()) {
		return;
	}
	this->connections[v1].push_back(v2);
	this->connections[v2].push_back(v1);
}

void Geometry::define_face(std::vector<int> vertices) {
	auto loop_result = this->get_loop(vertices);

	// Not a valid face as there isnt a loop of connections
	if (!loop_result.has_value()) {
		return;
	}

	this->faces.push_back(Face(loop_result.value()));
}

std::vector<int> Geometry::get_neighbours(int vertex) {
	return this->connections[vertex];
}

// Vertices: vertex id's 
// Returns the vertices in order of the loop, or nullopt if there is no loop between the vertices
std::optional<std::vector<int>> Geometry::get_loop(std::vector<int> vertices) {
	// Depth first search
	std::vector<int> visited;
	std::stack<int> collapsed;
	
	int current = vertices[0];
	collapsed.push(current);

	while (collapsed.size() != 0) {
		current = collapsed.top();
		collapsed.pop();
		visited.push_back(current);

		auto neighbours = this->get_neighbours(current);
		for (int v : neighbours) {
			// If we havent already visited this node (prevents backtracking and repeating)
			// and it is one of the vertices in our loop
			if (std::find(visited.begin(), visited.end(), v) == visited.end() &&
				std::find(vertices.begin(), vertices.end(), v) != vertices.end()) {
				collapsed.push(v);
				break;
			}
		}
	}

	// If all the visited nodes arent the same as the input 
	// then it is not a loop
	if (visited.size() != vertices.size()) {
		return std::nullopt;
	}
	
	return visited;
}

bool Geometry::are_vertices_connected(int v1, int v2) {
	for (auto v : this->get_neighbours(v1)) {
		if (v == v2) 
			return true;
	}
	return false;
}

void Geometry::calculate_normals(GeometryShadingType shading_type) {
	for (int f = 0; f < this->faces.size(); f++)
		this->calculate_face_normals(f, shading_type);
} 

Mesh Geometry::triangulate() {
	std::vector<Triangle> triangles = std::vector<Triangle>();
	for (Face face : this->faces) {
		std::vector<TriangleIds> triangle_ids = face.triangulate();
		for (auto triangle_id : triangle_ids) {
			Vertex v0 = this->vertices[triangle_id.v0];
			Vertex v1 = this->vertices[triangle_id.v1];
			Vertex v2 = this->vertices[triangle_id.v2];

			// Set vertex colour to face colour
			v0.colour = face.face_colour;
			v1.colour = face.face_colour;
			v2.colour = face.face_colour;

			if (face.shading_type == SHADE_FLAT) {
				v0.normal = face.face_normal;
				v1.normal = face.face_normal;
				v2.normal = face.face_normal;
			}

			Triangle triangle = Triangle(v0, v1, v2);
			triangles.push_back(triangle);
		}
	}

	Mesh triangulated = Mesh(triangles.data(), triangles.size());
	triangulated.transform = this->transform;

	return triangulated;
}

//Geometry Geometry::copy();