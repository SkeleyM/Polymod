#pragma once
#include <string>
#include <EMath.h>

#include "glad/glad.h"
static const char* DEFAULT_VERTEX_SHADER =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 o_pos;\n"
"void main()\n"
"{\n"
"	mat4 mvp = projection * view * model;\n"
"	o_pos = (mvp * vec4(pos, 1.0)).xyz;\n"
"	gl_Position = mvp * vec4(pos, 1.0);\n"
"}\n\0";

static const char* DEFAULT_FRAGMENT_SHADER =
"#version 330 core\n"
"in vec3 o_pos;\n"
"void main()\n"
"{\n"
"	float col = ((1.0 / o_pos.z)) - 0.5;\n"
"	gl_FragColor = vec4(col, col, col, 0.0);\n"
"}\n\0";

class Shader
{
public:
	GLuint gl_program_id;
	bool compilation_status;

	Shader(std::string vertex_source, std::string fragment_source);
	Shader();
	~Shader();

	void set_uniform_matrix4x4(std::string name, Matrix4x4 value);
	void set_uniform_float(std::string name, float value);
private:

};
