#include <iostream>
#include <Engine.h>
#include <InputManager.h>

#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>
#include <Renderer/Mesh.h>
#include <EMath.h>
#include <imgui.h>

#include <OrbitalCameraController.h>
#include <GeometryEditor.h>
#include <Ui/MenuBar.h>

#include <Ui/ToolbarTool/MoveTool.h>
#include <Ui/ToolbarTool/RotateTool.h>
#include <Ui/ToolbarTool/ScaleTool.h>
#include <Ui/ToolbarTool/ExtrudeTool.h>
#include <Ui/ToolbarTool/VertexSpinTool.h>

OrbitalCameraController* camera_controller;
GeometryEditor geometry_editor;

MenuBar menubar;

static void on_render() {
	static Vector2 mouse_pos{ 0.0f, 0.0f };
	
	InputManager& input = InputManager::get();

	// Calculate change in mouse position
	Engine* engine = Engine::get_instance();
	Vector2 new_pos = input.get_mouse_pos();

	Vector2 mouse_delta = new_pos - mouse_pos;
	mouse_pos = new_pos;

	// If left clicking rotate using the change in mouse position.
	if (engine->get_left_mouse() && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem))
		camera_controller->rotate_from_screen_xy(-mouse_delta.x, mouse_delta.y);

	camera_controller->set_orbit_radius(
		camera_controller->get_orbit_radius()
		+ (input.get_scroll().y)
	);

	menubar.render();

	geometry_editor.render();
	if (input.get_mouse_buttons().first) {
		geometry_editor.select(input.get_mouse_pos());
	}
}

int main() {
	Engine* engine = new Engine("Modeller", 1920, 1080);

	engine->set_on_render(on_render);
	Scene& scene = engine->get_active_scene();
	scene.light.position = Vector3(5.0f, 5.0f, 2.0f);

	// Move the camera back so that we are not in the same position as the square
	scene.camera.transform.translate(Vector3(0.0f, -1.5f, -1.0f));

	camera_controller = new OrbitalCameraController(&scene.camera);

	geometry_editor.get_geometry_manager().create_new_geometry("Test");
	auto geometry = geometry_editor.get_geometry_manager().get_geometry("Test");
	geometry_editor.set_current_geometry(geometry);
	geometry_editor.select_mode = Select_Face;

	Geometry& geometry_d = *geometry.lock().get();

	geometry_d.add_vertex(Vector3(-0.5f, -0.5f, 0.0f));
	geometry_d.add_vertex(Vector3(-0.5f, 0.5f, 0.0f));
	geometry_d.add_vertex(Vector3(0.5f, 0.5f, 0.0f));
	geometry_d.add_vertex(Vector3(0.5f, -0.5f, 0.0f));
			
	geometry_d.add_connection(0, 1);
	geometry_d.add_connection(1, 2);
	geometry_d.add_connection(2, 3);
	geometry_d.add_connection(3, 0);
			
	geometry_d.define_face({ 0, 1, 2, 3 });
	geometry_d.calculate_normals(SHADE_FLAT);
	
	Mesh mesh = geometry_d.triangulate();
	scene.add_mesh(mesh);


	Toolbar& toolbar = geometry_editor.get_toolbar();

	toolbar.add_tool(new MoveTool());
	toolbar.add_tool(new ScaleTool());
	toolbar.add_tool(new RotateTool());
	toolbar.add_tool(new ExtrudeTool());
	toolbar.add_tool(new VertexSpinTool());

	while (engine->should_keep_ticking()) {
		engine->tick();
		
		camera_controller->update();
	}

	return 0;
}