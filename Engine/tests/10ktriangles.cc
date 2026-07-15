#include <iostream>
#include <Engine.h>
#include <chrono>

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

static std::chrono::milliseconds tim;
static int fps_counter{ 0 };

static void on_render() {
	auto now = std::chrono::system_clock::now();
	auto new_tim = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

	fps_counter++;
	if ((new_tim - tim).count() > 1000) {
		std::cout << "FPS: " << fps_counter << std::endl;
		tim = new_tim;
		fps_counter = 0;
	}
}

int main() {
	Engine* engine = new Engine("Window", 1920, 1080);

	engine->set_on_render(on_render);
	Scene& scene = engine->get_active_scene();
	scene.add_mesh(mesh);

	// Testing 
	// Create a mesh with 1000 triangles
	const int t_c = 1000;
	auto triangles = (Triangle*)malloc(sizeof(Triangle) * t_c);
	for (int t = 0; t < t_c; t += 2) {
		triangles[t] = Triangle(
			Vertex(Vector3(-0.5f, -0.5f, -t)),
			Vertex(Vector3(-0.5f, 0.5f, -t)),
			Vertex(Vector3(0.5f, 0.5f, -t))
		);
		triangles[t + 1] = Triangle(
			Vertex(Vector3(0.5f, 0.5f, -t)),
			Vertex(Vector3(-0.5f, -0.5f, -t)),
			Vertex(Vector3(0.5f, -0.5f, -t))
		);
	}

	Mesh bigmesh = Mesh(triangles, t_c);
	scene.add_mesh(bigmesh);

	// Move the camera back so that we are not in the same position as the square
	scene.camera.transform.translate(Vector3(0.0f, -1.5f, -1.0f));

	while (engine->should_keep_ticking()) {
		engine->tick();
	}
	return 0;
}