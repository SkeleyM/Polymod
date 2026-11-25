#include <Renderer/Glerror.h>
#include <Renderer/TriangleRenderer.h>

TriangleRenderer::TriangleRenderer() {
	// Ensure the depth test is enabled, IMGUI may disable it
	glEnable(GL_DEPTH_TEST);
}

TriangleRenderer::~TriangleRenderer() {}

void TriangleRenderer::render(Camera& camera, std::shared_ptr<Mesh> mesh) {
	// Bind the buffer objects
	glBindVertexArray(this->meshbuffer.gl_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->meshbuffer.gl_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->meshbuffer.gl_ebo);

	// Attach the shader
	glUseProgram(this->shader.gl_program_id);

	this->shader.set_uniform_matrix4x4("model", mesh->transform.get_matrix());
	this->shader.set_uniform_matrix4x4("view", glm::inverse(camera.transform.get_matrix()));
	this->shader.set_uniform_matrix4x4("projection", camera.get_projection_matrix());

	// Ensure to follow through to each child mesh and draw those too
	std::shared_ptr<Mesh> current_mesh = mesh;
	while (current_mesh != nullptr) {
		// Texture uniforms
		if (current_mesh->material) {
			auto& material = current_mesh->material;
			this->shader.set_uniform_texture(material->texture);
			this->shader.set_uniform_bool("use_texture", material->use_texture);
			this->shader.set_uniform_vector4("albedo_colour", material->albedo_colour);
			this->shader.set_uniform_bool("use_albedo_colour", material->use_albedo_colour);
		}

		// Get the info about the mesh on the gpu and draw it
		GpuMesh gpumesh = this->meshbuffer.get_gpu_mesh(current_mesh);

		glDrawElements(
			GL_TRIANGLES,
			current_mesh->triangle_count * 3,
			GL_UNSIGNED_INT,
			(void*)gpumesh.ebo_offset
		);

		current_mesh = current_mesh->child;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	gl_check_for_error();
}

void TriangleRenderer::set_shader(Shader shader) {
	shader.dont_destroy();
	this->shader = shader;
}

void TriangleRenderer::delete_mesh_from_buffer(std::shared_ptr<Mesh> mesh) {
	// Delete mesh and all of its children
	auto& current_mesh = mesh;
	while (current_mesh != nullptr) {
		this->meshbuffer.delete_mesh(mesh);
		current_mesh = current_mesh->child;
	}
}