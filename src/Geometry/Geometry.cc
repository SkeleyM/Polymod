#include <Geometry/Geometry.h>

void Geometry::add_vertex(Vector3 vertex) {
	Vertex vert = Vertex(vertex);
	this->vertices.push_back(vert);
}

void Geometry::add_connection(int v1, int v2) {
	this->connections[v1].push_back(v2);
	this->connections[v2].push_back(v1);
}

void Geometry::define_face(std::vector<int> vertices) {
	this->faces.push_back(Face(vertices));
}

std::vector<int> Geometry::get_neighbours(int vertex) {
	return this->connections[vertex];
}

Mesh Geometry::triangulate() {
	std::vector<Triangle> triangles = std::vector<Triangle>();
	for (Face face : this->faces) {
		std::vector<TriangleIds> triangle_ids = face.triangulate();
		
		for (auto triangle : triangle_ids) {
			Vertex v0 = this->vertices[triangle.v0];
			Vertex v1 = this->vertices[triangle.v1];
			Vertex v2 = this->vertices[triangle.v2];
			Triangle triangle = Triangle(v0, v1, v2);
			triangles.push_back(triangle);
		}
	}
	Mesh triangulated = Mesh(triangles.data(), triangles.size());
	triangulated.transform = this->transform;

	return triangulated;
}

//Geometry Geometry::copy();