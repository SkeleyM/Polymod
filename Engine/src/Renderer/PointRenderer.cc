#include <glad/glad.h>
#include <Renderer/PointRenderer.h>
#include <Renderer/Glerror.h>

PointRenderer::PointRenderer() {
	this->shader = new Shader(POINT_VERTEX_SHADER, POINT_FRAGMENT_SHADER);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)sizeof(Vector3));
}

void PointRenderer::set_point_size(float size) {
	point_size = size;
}

void PointRenderer::render_points(Camera& camera, std::vector<Point>& points) {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glUseProgram(this->shader->gl_program_id);

	this->shader->set_uniform_matrix4x4("model", Matrix4x4(1.0f));
	this->shader->set_uniform_matrix4x4("view", glm::inverse(camera.transform.get_matrix()));
	this->shader->set_uniform_matrix4x4("projection", camera.get_projection_matrix());

	glPointSize(point_size);

	// Draw the points
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Point), points.data(), GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, points.size());

	glUseProgram(0);
	glBindVertexArray(0);

	gl_check_for_error();
}

void PointRenderer::render_point(Camera& camera, Point& point) {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glUseProgram(this->shader->gl_program_id);

	this->shader->set_uniform_matrix4x4("model", Matrix4x4(1.0f));
	this->shader->set_uniform_matrix4x4("view", glm::inverse(camera.transform.get_matrix()));
	this->shader->set_uniform_matrix4x4("projection", camera.get_projection_matrix());

	glPointSize(point_size);

	// Draw the points
	glBufferData(GL_ARRAY_BUFFER, sizeof(Point), &point, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_POINTS, 0, 1);

	glUseProgram(0);
	glBindVertexArray(0);

	gl_check_for_error();
}