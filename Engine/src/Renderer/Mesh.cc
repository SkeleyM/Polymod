#include <Renderer/Mesh.h>

Mesh::Mesh(Triangle triangles[], uint32_t triangle_count) {
	// Malloc instead of new to avoid needing a default constructor
	Triangle* mesh_triangles = (Triangle*)malloc(sizeof(Triangle) * triangle_count);
	if (!mesh_triangles) {
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < triangle_count; i++) {
		mesh_triangles[i] = triangles[i];
	}
	this->triangles = mesh_triangles;
	this->triangle_count = triangle_count;
}

Mesh::~Mesh() {
	free(this->triangles);
}

// Copy Constructor
Mesh::Mesh(const Mesh& mesh) {
	// Malloc instead of new to avoid needing a default constructor
	Triangle* mesh_triangles = (Triangle*)malloc(sizeof(Triangle) * mesh.triangle_count);
	if (!mesh_triangles) {
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < mesh.triangle_count; i++) {
		mesh_triangles[i] = mesh.triangles[i];
	}
	this->triangles = mesh_triangles;
	this->triangle_count = mesh.triangle_count;
}

std::vector<uint32_t> Mesh::get_indices() {
	std::vector<uint32_t> indices(this->triangle_count * 3);

	for (int i = 0; i < this->triangle_count * 3; i++) {
		indices[i] = i;
	}
	return indices;
}