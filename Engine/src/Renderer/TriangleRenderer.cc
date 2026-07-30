#include <Renderer/Glerror.h>
#include <Renderer/TriangleRenderer.h>

TriangleRenderer::TriangleRenderer() {
	// Ensure the depth test is enabled, IMGUI may disable it
	glEnable(GL_DEPTH_TEST);
}

TriangleRenderer::~TriangleRenderer() {}

void TriangleRenderer::render(Camera& camera, Mesh* mesh) {
	// Get the info about the mesh on the gpu and draw it
	GpuMesh gpumesh = this->meshbuffer.get_gpu_mesh(*mesh);

	// Bind the buffer objects
	glBindVertexArray(this->meshbuffer.gl_vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->meshbuffer.gl_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->meshbuffer.gl_ebo);

	// Attach the shader
	glUseProgram(this->shader.gl_program_id);

	this->shader.set_uniform_matrix4x4("model", mesh->transform.get_matrix());
	this->shader.set_uniform_matrix4x4("view", glm::inverse(camera.transform.get_matrix()));
	this->shader.set_uniform_matrix4x4("projection", camera.get_projection_matrix());

 	glDrawElements(
		GL_TRIANGLES, 
		mesh->triangle_count * 3, 
		GL_UNSIGNED_INT, 
		(void*)gpumesh.ebo_offset
	); 

	gl_check_for_error();
}

void TriangleRenderer::set_shader(Shader shader) {
	this->shader = shader;
}
