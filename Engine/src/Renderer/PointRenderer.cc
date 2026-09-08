#pragma once

#include <glad/glad.h>
#include <Renderer/PointRenderer.h>

void PointRenderer::set_point_size(float size) {
	point_size = size;
}

void PointRenderer::render_points(std::vector<Point>& points) {
	// Using immediate mode for ease, no need for efficient rendering.
	glPointSize(point_size);
	glBegin(GL_POINTS);

	for (Point& point : points) {
		glColor3f(point.colour.x, point.colour.y, point.colour.z);
		glVertex3f(point.position.x, point.position.y, point.position.z);
	}
	
	glEnd();
}

void PointRenderer::render_point(Point& point) {
	glPointSize(point_size);
	glBegin(GL_POINTS);
	
	glColor3f(point.colour.x, point.colour.y, point.colour.z);
	glVertex3f(point.position.x, point.position.y, point.position.z);

	glEnd();
}