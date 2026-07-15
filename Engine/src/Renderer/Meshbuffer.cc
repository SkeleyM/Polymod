#include <Renderer/Glerror.h>
#include <Renderer/MeshBuffer.h>

#include <iostream>
#include <algorithm>

MeshBuffer::MeshBuffer(int size) {
	this->size = size;

	// Generate the buffers used for storing mesh and vertex data
	glGenVertexArrays(1, (GLuint*)&this->gl_vao);
	gl_check_for_error();
	glGenBuffers(1, (GLuint*)&this->gl_vbo);
	gl_check_for_error();
	glGenBuffers(1, (GLuint*)&this->gl_ebo);
	gl_check_for_error();

	// Initialise buffers with empty data
	glBindVertexArray(this->gl_vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->gl_vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Triangle), NULL, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->gl_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), NULL, GL_DYNAMIC_DRAW);

	// Set vertex attributes
	// Vertex attributes allow shaders to access vertex data
	// For now my vertex struct is just the position of the vertex
	// 
	// Set position vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);
	glEnableVertexAttribArray(0);
	gl_check_for_error();
}

MeshBuffer::~MeshBuffer() {
}

void MeshBuffer::add_mesh(Mesh& mesh) {
	auto gpu_mesh_gap_result = this->create_gpu_mesh(mesh);

	if (!gpu_mesh_gap_result.has_value()) {
		// Throw an error for now, in the future growing the buffer
		// might be a better solution
		throw std::range_error::exception();
	}
	GpuMesh gpu_mesh = *gpu_mesh_gap_result;


	std::vector<uint32_t> indices = mesh.get_indices();
	// Calculate the incices
	for (int i = 0; i < indices.size(); i++) {
		indices[i] = indices[i] + (gpu_mesh.ebo_offset / sizeof(uint32_t));
	}

	
	glBindVertexArray(this->gl_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->gl_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->gl_ebo);

	// Upload Vertex data to gpu
	glBufferSubData(GL_ARRAY_BUFFER, gpu_mesh.vbo_offset, gpu_mesh.vbo_size, mesh.triangles);
	// Upload Index data to gpu
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, gpu_mesh.ebo_offset, gpu_mesh.ebo_size, indices.data());

	gl_check_for_error();

	this->mesh_map.insert({ mesh.id, gpu_mesh });
}

std::optional<GpuMesh> MeshBuffer::create_gpu_mesh(Mesh& mesh) {
	uint32_t ebo_size = mesh.triangle_count * 3 * sizeof(uint32_t);
	uint32_t vbo_size = mesh.triangle_count * 3 * sizeof(Vertex);

	// To append to the buffer, this algorithm requires at least 1 mesh to already exist
	if (this->mesh_map.size() == 0) {
		return GpuMesh(
			0,
			ebo_size,
			0,
			vbo_size
		);
	}

	// Get all the gpu meshes
	std::vector<GpuMesh> meshes;
	for (auto [k, v] : this->mesh_map) {
		meshes.push_back(v);
	}

	// Sort in ebo offset ascending
	std::sort(meshes.begin(), meshes.end(), [](GpuMesh a, GpuMesh b) {
		return a.ebo_offset < b.ebo_offset;
	});

	uint32_t ebo_offset = meshes.back().ebo_offset + meshes.back().ebo_size ;

	// Sort in vbo offset ascending
	std::sort(meshes.begin(), meshes.end(), [](GpuMesh a, GpuMesh b) {
		return a.vbo_offset < b.vbo_offset;
		});
	uint32_t vbo_offset = meshes.back().vbo_offset + meshes.back().vbo_size;

	// Bounds check to ensure this doesnt overflow the buffer
	if (((ebo_offset + ebo_size) > this->size * sizeof(uint32_t)) 
		|| ((vbo_offset + vbo_size) > size * sizeof(Triangle))) {
		// This will overflow the buffer, so return no value.
		return std::nullopt;
	}

	return GpuMesh(
		ebo_offset,
		ebo_size,
		vbo_offset,
		vbo_size
	);
}

void MeshBuffer::clear_buffer() {
	this->mesh_map.clear();
}

GpuMesh MeshBuffer::get_gpu_mesh(Mesh& mesh) {
	// If the mesh already exists on the gpu, return the GpuMesh for it.
	if (this->mesh_map.find(mesh.id) != this->mesh_map.end()) {
		return this->mesh_map[mesh.id];
	}
	
	this->add_mesh(mesh);
	return this->get_gpu_mesh(mesh);
}