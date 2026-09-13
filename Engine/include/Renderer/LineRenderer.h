#pragma once

#include <vector>
#include <EMath.h>

#include <Engine.h>
#include <Renderer/Shader.h>

static const char* LINE_VERTEX_SHADER =
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

static const char* LINE_FRAGMENT_SHADER =
"#version 330 core\n"
"in vec3 o_colour;\n"
"void main()\n"
"{\n"
"	gl_FragColor = vec4(o_colour, 0.0);\n"
"}\n\0";

struct Line {
	Vector3 start;
	Vector3 end;
	Vector3 colour;
};

class LineRenderer {
private:
	float line_width = 1.0f;
	Shader* shader;
	unsigned int vao;
	unsigned int vbo;
public:
	LineRenderer();

	void set_line_width(float width);
	void render_lines(Camera& camera, std::vector<Line>& lines);
	void render_line(Camera& camera, Line& line);
};