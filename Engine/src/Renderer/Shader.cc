#include <Renderer/Glerror.h>
#include <Renderer/Shader.h>
// READ: Decided no point in a manually compiling shader, just auto compile

Shader::Shader() : Shader::Shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER) {}

Shader::Shader(std::string vertex_source, std::string fragment_source)
{
	compilation_status = false;

	gl_program_id = glCreateProgram();

	auto vertex = glCreateShader(GL_VERTEX_SHADER);
	auto fragment = glCreateShader(GL_FRAGMENT_SHADER);

	// Give the gpu driver the source code to the shader before compilation
	auto vertex_len = vertex_source.length();
	auto fragment_len = fragment_source.length();
	auto v_source = vertex_source.c_str();
	auto f_source = fragment_source.c_str();
	glShaderSource(vertex, 1, (GLchar* const*)(&v_source), (const GLint*)(&vertex_len));
	glShaderSource(fragment, 1, (GLchar* const*)(&f_source), (const GLint*)(&fragment_len));

	glCompileShader(vertex);
	glCompileShader(fragment);

	// Check if both shaders compiled
	GLint vertex_compile_status;
	GLint fragment_compile_status;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertex_compile_status);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragment_compile_status);

	if (!(vertex_compile_status && fragment_compile_status)) {
		compilation_status = false;
		return;
	}

	// Attach both shaders to the program, so that they can be linked.
	glAttachShader(gl_program_id, vertex);
	glAttachShader(gl_program_id, fragment);
	glLinkProgram(gl_program_id);

	// Check if the shader program successfully linked
	GLint link_status;
	glGetProgramiv(gl_program_id, GL_LINK_STATUS, &link_status);

	// Now that program is linked we dont need these resources on the gpu
	// So detach and delete them
	glDetachShader(gl_program_id, vertex);
	glDetachShader(gl_program_id, fragment);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	gl_check_for_error();

	// True if all compiled and linked successfully.
	compilation_status = link_status && vertex_compile_status && fragment_compile_status;
}

Shader::~Shader()
{
	glDeleteProgram(gl_program_id);
	this->compilation_status = false;
}

void Shader::set_uniform_matrix4x4(std::string name, Matrix4x4 value) {
	// Get the uniforms location required to set the value in the shader
	auto uniform_location = glGetUniformLocation(this->gl_program_id, name.c_str());
	if (uniform_location == -1) {
		std::cerr << "Attempted to set uniform which does not exist";
		return;
	}

	// Set the uniform value in the shader
	glUniformMatrix4fv(uniform_location, 1, GL_FALSE, (float*)(&value));
}

void Shader::set_uniform_float(std::string name, float value) {
	// Get the uniforms location required to set the value in the shader
	auto uniform_location = glGetUniformLocation(this->gl_program_id, name.c_str());
	if (uniform_location == -1) {
		std::cerr << "Attempted to set uniform which does not exist";
		return;
	}

	// Set the uniform value in the shader
	glUniform1f(uniform_location, value);
}