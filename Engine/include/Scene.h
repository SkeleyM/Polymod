#pragma once
#include <vector>

#include <Light.h>
#include <Renderer/Camera.h>
#include <Renderer/Mesh.h>
#include <Renderer/TriangleRenderer.h>

class Scene {
	TriangleRenderer renderer;
	std::vector<Mesh> meshes;
public:
	Light light;
	Camera camera{Camera(90.0f, 0.001f, 1000.0f)};

	Scene();
	~Scene();

	void render();
	void add_mesh(Mesh mesh);
};