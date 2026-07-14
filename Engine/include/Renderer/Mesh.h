#pragma once
#include <Renderer/Triangle.h>
#include <Transform.h>

#include <vector>

typedef struct Mesh {
public:
	// To avoid using a dynamic array for storing mesh data
	// memory is manually allocated and tracked using the 'triangle_count' variable.
	// A dynamic array is nessicary as meshes are different sizes;
	uint32_t triangle_count;
	Triangle* triangles;

	Transform transform;

	Mesh(Triangle triangles[], uint32_t triangle_count);
	Mesh(const Mesh& mesh);
	~Mesh();

	std::vector<uint32_t> get_indices();
} Mesh;