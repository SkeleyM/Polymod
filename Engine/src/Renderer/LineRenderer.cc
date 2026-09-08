#include <Renderer/LineRenderer.h>
#include <glad/glad.h>

void LineRenderer::set_line_width(float width) {
	this->line_width = width;
}

void LineRenderer::render_lines(std::vector<Line>& lines) {
	glLineWidth(this->line_width);
	glBegin(GL_LINES);

	for (Line line : lines) {
		glColor3f(line.colour.x, line.colour.y, line.colour.z);
		glVertex3f(line.start.x, line.start.y, line.start.z);
		glVertex3f(line.end.x, line.end.y, line.end.z);
	}

	glEnd();
}

void LineRenderer::render_line(Line& line) {
	glLineWidth(this->line_width);
	glBegin(GL_LINES);

	glColor3f(line.colour.x, line.colour.y, line.colour.z);
	glVertex3f(line.start.x, line.start.y, line.start.z);
	glVertex3f(line.end.x, line.end.y, line.end.z);

	glEnd();
}