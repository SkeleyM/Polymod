#pragma once

#include <Renderer/Camera.h>
#include <Renderer/Shader.h>
#include <EMath.h>


static const char* POINT_VERTEX_SHADER =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"layout (location = 1) in vec3 colour;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 o_colour;\n"
"void main()\n"
"{\n"
"	mat4 mvp = projection * view * model;\n"
"	vec4 position = view * model * vec4(pos, 1.0);\n"
"	o_colour = colour;\n"
"	gl_Position = mvp * vec4(pos, 1.0);\n"
"}\n\0";

static const char* POINT_FRAGMENT_SHADER =
"#version 330 core\n"
"in vec3 o_colour;\n"
"void main()\n"
"{\n"
"	gl_FragColor = vec4(o_colour, 0.0);\n"
"}\n\0";

struct Point {
	Vector3 position;
	Vector3 colour;
};

class PointRenderer {
private:
	float point_size = 1.0f;

	Shader* shader;
	unsigned int vao;
	unsigned int vbo;
public:
	PointRenderer();

	void set_point_size(float size);
	void render_points(Camera& camera, std::vector<Point>& points);
	void render_point(Camera& camera, Point& point);
};