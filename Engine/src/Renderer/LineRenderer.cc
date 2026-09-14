#include <Renderer/LineRenderer.h>
#include <glad/glad.h>

#include <Renderer/Glerror.h>

LineRenderer::LineRenderer() {
	this->shader = new Shader(LINE_VERTEX_SHADER, LINE_FRAGMENT_SHADER);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3) * 2, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3) * 2, (void*)sizeof(Vector3));
}

void LineRenderer::set_line_width(float width) {
	this->line_width = width;
}

void LineRenderer::render_lines(Camera& camera, const std::vector<Line>& lines) {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glUseProgram(this->shader->gl_program_id);

	this->shader->set_uniform_matrix4x4("model", Matrix4x4(1.0f));
	this->shader->set_uniform_matrix4x4("view", glm::inverse(camera.transform.get_matrix()));
	this->shader->set_uniform_matrix4x4("projection", camera.get_projection_matrix());

	// Data for the lines needs to be structured differently.
	std::vector<Vector3> line_data;
	for (const Line& line : lines) {
		line_data.push_back(line.start);
		line_data.push_back(line.colour);
		line_data.push_back(line.end);
		line_data.push_back(line.colour);
	}

	glLineWidth(this->line_width);

	// Draw the lines
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * line_data.size(), line_data.data(), GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINES, 0, lines.size() * 2);

	glBindVertexArray(0);
	glUseProgram(0);

	gl_check_for_error();
}

void LineRenderer::render_line(Camera& camera, const Line& line) {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glUseProgram(this->shader->gl_program_id);

	this->shader->set_uniform_matrix4x4("model", Matrix4x4(1.0f));
	this->shader->set_uniform_matrix4x4("view", glm::inverse(camera.transform.get_matrix()));
	this->shader->set_uniform_matrix4x4("projection", camera.get_projection_matrix());

	glLineWidth(this->line_width);

	// Data for the lines needs to be structured differently.
	std::vector<Vector3> line_data;
	line_data.push_back(line.start);
	line_data.push_back(line.colour);
	line_data.push_back(line.end);
	line_data.push_back(line.colour);

	// Draw the lines
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * line_data.size(), line_data.data(), GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINES, 0, 2);

	glBindVertexArray(0);
	glUseProgram(0);

	gl_check_for_error();
}