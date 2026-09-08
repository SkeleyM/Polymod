#pragma once

#include <Renderer/Camera.h>
#include <Renderer/Shader.h>
#include <EMath.h>

struct Point {
	Vector3 position;
	Vector3 colour;
};

class PointRenderer {
private:
	float point_size = 1.0f;
public:
	void set_point_size(float size);
	void render_points(std::vector<Point>& points);
	void render_point(Point& point);
};