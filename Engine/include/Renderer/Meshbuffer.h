#pragma once
#include <glad/glad.h>

#include <Renderer/Mesh.h>

#include <optional>

struct GpuMesh {
	uint32_t ebo_offset;
	uint32_t ebo_size;
	uint32_t vbo_offset;
	uint32_t vbo_size;

	GpuMesh() {
		this->ebo_offset = 0;
		this->ebo_size = 0;
		this->vbo_offset = 0;
		this->vbo_size = 0;
	}

	GpuMesh(uint32_t ebo_offset, uint32_t ebo_size, uint32_t vbo_offset, uint32_t vbo_size) {
		this->ebo_offset = ebo_offset;
		this->ebo_size = ebo_size;
		this->vbo_offset = vbo_offset;
		this->vbo_size = vbo_size;
	}
};

class MeshBuffer {
public:
	uint32_t gl_vao;
	uint32_t gl_vbo;
	uint32_t gl_ebo;

	// Needed to track size for bounds checking the buffer
	uint32_t size; 

	std::unordered_map<Mesh*, GpuMesh> mesh_map;

	MeshBuffer(int size);
	~MeshBuffer();

	void add_mesh(Mesh& mesh);
	// This function finds a place in the buffer by attempting to append
	// from the last item
	std::optional<GpuMesh> create_gpu_mesh(Mesh& mesh);
	void clear_buffer();

	GpuMesh get_gpu_mesh(Mesh& mesh);
};