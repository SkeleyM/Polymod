#pragma once
#include <Renderer/Camera.h>
#include <Renderer/MeshBuffer.h>
#include <Renderer/Shader.h>

#include <glad/glad.h>

#define MAX_TRIANGLES 10000

class TriangleRenderer {
private:
	Shader shader;
	MeshBuffer meshbuffer{ MeshBuffer(MAX_TRIANGLES) };
public:
	TriangleRenderer();
	~TriangleRenderer();

	void render(Camera& camera, Mesh* mesh);
	void set_shader(Shader shader);
	Shader& get_shader() { return this->shader; }
};