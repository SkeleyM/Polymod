#pragma once
#include <string>
#include <EMath.h>

#include "glad/glad.h"
static const char* DEFAULT_VERTEX_SHADER =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"layout (location = 1) in vec3 normal;\n"
"layout (location = 2) in vec3 colour;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 world_position;\n"
"out vec3 v_normal;\n"
"out vec3 v_colour;\n"
"void main()\n"
"{\n"
"	mat4 mvp = projection * view * model;\n"
"	vec4 position = view * model * vec4(pos, 1.0);\n"
"	world_position = position.xyz;\n"
"	v_normal = normal;\n"
"	v_colour = colour;\n"
"	gl_Position = mvp * vec4(pos, 1.0);\n"
"}\n\0";

static const char* DEFAULT_FRAGMENT_SHADER =
"#version 330 core\n"
"in vec3 world_position;\n"
"in vec3 v_normal;\n"
"in vec3 v_colour;\n"
"uniform vec3 light_position;\n"
"uniform vec3 light_colour;\n"
"vec3 diffuse(vec3 normal, vec3 light_pos)\n"
"{\n"
"	vec3 ambient = vec3(0.4, 0.4, 0.4);\n"
"	vec3 lightVec = normalize(light_pos - world_position);\n"
"	vec3 colour = light_colour * max(dot(lightVec, normal), 0.3);\n"
"	return ambient + (colour * v_colour);\n"
"}\n"
"void main()\n"
"{\n"
"	gl_FragColor = vec4(diffuse(v_normal, light_position), 0.0);\n"
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
	void set_uniform_vector3(std::string name, Vector3 value);
	void set_uniform_float(std::string name, float value);
};