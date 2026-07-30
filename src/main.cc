#include <iostream>
#include <Engine.h>

#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>
#include <Renderer/Mesh.h>
#include <EMath.h>
#include <GLFW/glfw3.h>

#include <OrbitalCameraController.h>
#include <Geometry/Geometry.h>

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

OrbitalCameraController* camera_controller;

static void on_render() {
	static Vector2 mouse_pos{ 0.0f, 0.0f };

	// Calculate change in mouse position
	Engine* engine = Engine::get_instance();
	Vector2 new_pos = engine->get_mouse_position();

	Vector2 mouse_delta = new_pos - mouse_pos;
	mouse_pos = new_pos;

	// If left clicking rotate using the change in mouse position.
	if (engine->get_left_mouse())
		camera_controller->rotate_from_screen_xy(mouse_delta.x, mouse_delta.y);
}

int main() {
	Engine* engine = new Engine("Window", 1920, 1080);

	engine->set_on_render(on_render);
	Scene& scene = engine->get_active_scene();
	//scene.add_mesh(mesh);

	// Move the camera back so that we are not in the same position as the square
	scene.camera.transform.translate(Vector3(0.0f, -1.5f, -1.0f));

	camera_controller = new OrbitalCameraController(&scene.camera);
	camera_controller->set_orbit_origin(mesh.transform.position);
	camera_controller->rotate_from_screen_xy(0.0, 5);

	// Test the geometry
	Geometry geometry;
	geometry.add_vertex(Vector3(-0.5f, -0.5f, 0.0f));
	geometry.add_vertex(Vector3(-0.5f, 0.5f, 0.0f));
	geometry.add_vertex(Vector3(0.5f, 0.5f, 0.0f));

	geometry.add_vertex(Vector3(0.5f, -0.5f, 0.0f));

	geometry.define_face({ 0, 1, 2, 3});

	Mesh mes = geometry.triangulate();
	scene.add_mesh(mes);

	while (engine->should_keep_ticking()) {
		engine->tick();

		//camera_controller->set_orbit_radius(5 * (sin(t) + 1));
		camera_controller->update();
	}
	return 0;
}