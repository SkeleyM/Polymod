#include <iostream>
#include <Engine.h>

#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>
#include <Renderer/Mesh.h>

#include <EMath.h>

Triangle t = Triangle(
	Vertex(Vector3(-0.5f, -0.5f, 0.0f)),
	Vertex(Vector3(-0.5f, 0.5f, 0.0f)),
	Vertex(Vector3(0.5f, 0.5f, 0.0f))

);

Triangle t2 = Triangle(
	Vertex(Vector3(0.5f, 0.5f, 0.0f)),
	Vertex(Vector3(-0.5f, -0.5f, 0.0f)),
	Vertex(Vector3(0.5f, -0.5f, 0.0f))
);

Triangle tris[] = { t, t2 };
Mesh mesh = Mesh(tris, sizeof(tris) / sizeof(Triangle));

static void on_render() {}

int main() {
	Engine* engine = new Engine("Window", 1920, 1080);

	engine->set_on_render(on_render);
	Scene& scene = engine->get_active_scene();
	scene.add_mesh(mesh);

	// Move the camera back so that we are not in the same position as the square
	scene.camera.transform.translate(Vector3(0.0f, 0.0f, -1.0f));
	
	while (engine->should_keep_ticking()) {
		engine->tick();
	}
	return 0;
}