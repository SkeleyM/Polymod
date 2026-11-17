#pragma once
#include <Renderer/Triangle.h>
#include <Renderer/Texture.h>
#include <Transform.h>

#include <vector>
#include <memory>

typedef struct Mesh {
	friend class MeshBuffer;

	// To avoid using a dynamic array for storing mesh data
	// memory is manually allocated and tracked using the 'triangle_count' variable.
	// A dynamic array is nessicary as meshes are different sizes;
private:
	Triangle* triangles;

public:
	uint32_t triangle_count;
	std::shared_ptr<Texture> texture;

	Transform transform;

	Mesh(Triangle triangles[], uint32_t triangle_count);
	Mesh(const Mesh& mesh);
	~Mesh();

	std::vector<uint32_t> get_indices();
} Mesh;