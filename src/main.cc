#include <iostream>
#include <Engine.h>
#include <InputManager.h>

#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>
#include <Renderer/Mesh.h>
#include <EMath.h>
#include <imgui.h>

#include <AxisGrid.h>
#include <OrbitalCameraController.h>
#include <GeometryEditor.h>
#include <GeometryWireframeRenderer.h>
#include <ShortcutManager.h>
#include <Geometry/GeometryPrimitives.h>

#include <Ui/GeometryEditor/EditorModeSelector.h>
#include <Ui/GeometryEditor/SceneTree.h>
#include <Ui/MenuBar/Menu.h>
#include <Ui/MenuBar/MenuBar.h>
#include <Ui/MenuBar/MenuBarItem.h>
#include <Ui/Primitives/PrimitiveOperationPanels.h>
#include <Ui/ToolbarTool/MoveTool.h>
#include <Ui/ToolbarTool/RotateTool.h>
#include <Ui/ToolbarTool/ScaleTool.h>
#include <Ui/ToolbarTool/ExtrudeTool.h>
#include <Ui/ToolbarTool/VertexSpinTool.h>

#include <Renderer/LineRenderer.h>
#include <Renderer/PointRenderer.h>

#include <Geometry/Formats/GeometryFormats.h>

OrbitalCameraController* camera_controller = nullptr;
AxisGrid* axis_grid = nullptr;
EditorModeSelector* editor_mode_selector = nullptr;
SceneTree* scene_tree = nullptr;
GeometryWireframeRenderer* wireframe_renderer = nullptr;
GeometryEditor* geometry_editor = nullptr;
ShortcutManager shortcut_manager;

MenuBar menubar;

// main application render function, called by the engine
static void on_render() {
	InputManager& input = InputManager::get();
	static Vector2 mouse_pos{ 0.0f, 0.0f };
	static bool has_clicked = false;
	static bool clicked_this_frame = false;

	if (!has_clicked && input.get_mouse_buttons().first) {
		has_clicked = true;
		clicked_this_frame = true;
	}
	else if (has_clicked && input.get_mouse_buttons().first) {
		clicked_this_frame = false;
	}
	else {
		has_clicked = false;
		clicked_this_frame = false;
	}

	// Calculate change in mouse position
	Engine* engine = Engine::get_instance();
	Camera& active_camera = engine->get_active_scene().camera;
	Vector2 new_pos = input.get_mouse_pos();

	Vector2 mouse_delta = new_pos - mouse_pos;
	mouse_pos = new_pos;

	bool is_dragging = abs(mouse_delta.x + mouse_delta.y) > 10;

	// If left clicking rotate using the change in mouse position.
	if (input.get().get_mouse_buttons().first
		&& !(ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantCaptureMouse))
		camera_controller->rotate_from_screen_xy(-mouse_delta.x, mouse_delta.y);

	camera_controller->set_orbit_radius(
		camera_controller->get_orbit_radius()
		+ (input.get_scroll().y)
	);

	// Render all the UI
	menubar.render();
	geometry_editor->render();
	axis_grid->render(active_camera);
	editor_mode_selector->render();
	scene_tree->render();

	// Check that the mouse hasnt moved much this frame before we click
	if (clicked_this_frame && !is_dragging) {
		geometry_editor->select(input.get_mouse_pos());
	}

	std::weak_ptr<Geometry> current_geometry = geometry_editor->get_current_geometry();
	if (!current_geometry.expired()) {
		Geometry& geometry = *current_geometry.lock().get();
		SelectedGeometry selection = geometry_editor->get_selection();
		wireframe_renderer->render_wireframe(
			active_camera,
			geometry,
			selection
		);
	}
}

int main() {
	Engine* engine = new Engine("Polymodel", 1920, 1080);

	engine->set_on_render(on_render);
	Scene& scene = engine->get_active_scene();
	scene.light.position = Vector3(5.0f, 5.0f, 2.0f);

	// Move the camera back so that we are not in the same position as the square
	scene.camera.transform.translate(Vector3(0.0f, -1.5f, -1.0f));

	// Create all global variables
	geometry_editor = new GeometryEditor();
	wireframe_renderer = new GeometryWireframeRenderer();
	camera_controller = new OrbitalCameraController(&scene.camera);
	axis_grid = new AxisGrid();
	editor_mode_selector = new EditorModeSelector(geometry_editor);
	scene_tree = new SceneTree(geometry_editor);

	wireframe_renderer->set_edge_size(2.0f);
	wireframe_renderer->set_vertex_size(4.0f);

	// Initialise toolbar
	Toolbar& toolbar = geometry_editor->get_toolbar();

	toolbar.add_tool(new MoveTool());
	toolbar.add_tool(new ScaleTool());
	toolbar.add_tool(new RotateTool());
	toolbar.add_tool(new ExtrudeTool());
	toolbar.add_tool(new VertexSpinTool());

	// Initialise menus
	Menu file_menu("File");
	Menu edit_menu("Edit");
	Menu add_menu("Add");

	// Edit menu items
	MenuBarItem undo("Undo", []() {
		geometry_editor->undo();
		});
	MenuBarItem redo("Redo", []() {
		geometry_editor->redo();
		});
	edit_menu.add_menu_item(undo);
	edit_menu.add_menu_item(redo);

	// Add menu items
	MenuBarItem add_selector("Add Primitive", [&]() {
		auto create_primitive_tool = new CreatePrimitiveTool(GeometryPrimitives::Cube);
		toolbar.simulate_tool_click(create_primitive_tool);
		});
	add_menu.add_menu_item(add_selector);


	menubar.add_menu(file_menu);
	menubar.add_menu(edit_menu);
	menubar.add_menu(add_menu);

	// Add shortcuts
	shortcut_manager.add_shortcut({ GLFW_KEY_Z, MODIFIER_CONTROL, []() {
		geometry_editor->undo();
	}, true });

	shortcut_manager.add_shortcut({ GLFW_KEY_Z, MODIFIER_CONTROL | MODIFIER_SHIFT, []() {
		geometry_editor->redo();
	}, true });

	shortcut_manager.add_shortcut({ GLFW_KEY_ESCAPE, MODIFIER_NONE, []() {
		if (geometry_editor->is_performing_operation())
			geometry_editor->cancel_operation();
		else {
			geometry_editor->set_selection({});
		}
	}, true });

	// Tool shortcuts
	shortcut_manager.add_shortcut({ GLFW_KEY_E, MODIFIER_NONE, []() {
		Toolbar& toolbar = geometry_editor->get_toolbar();
		toolbar.simulate_tool_click(new ExtrudeTool());
	}, true });

	shortcut_manager.add_shortcut({ GLFW_KEY_S, MODIFIER_NONE, []() {
		Toolbar& toolbar = geometry_editor->get_toolbar();
		toolbar.simulate_tool_click(new ScaleTool());
	}, true });

	shortcut_manager.add_shortcut({ GLFW_KEY_R, MODIFIER_NONE, []() {
		Toolbar& toolbar = geometry_editor->get_toolbar();
		toolbar.simulate_tool_click(new RotateTool());
	}, true });

	shortcut_manager.add_shortcut({ GLFW_KEY_M, MODIFIER_NONE, []() {
		Toolbar& toolbar = geometry_editor->get_toolbar();
		toolbar.simulate_tool_click(new MoveTool());
	}, true });

	//	 test code
	auto format_factory = GeometryFormat::GeometryFormatFactory();
	auto spec = GeometryFormat::GeometryFormatSpec();
	spec.geometry_format = GeometryFormat::GeometryFormatType::WavefrontObj;

	auto format = format_factory.create_format(spec);
	GeometryFormat::GeometryFileHandler::export_geometry(format.get(), *geometry_editor->get_current_geometry().lock(), "./", "yay.obj");


	while (engine->should_keep_ticking()) {
		engine->tick();

		// Avoid using shortcuts whilst typing into an input field
		if (ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantCaptureMouse)
			shortcut_manager.ignore_shortcuts(true);
		else
			shortcut_manager.ignore_shortcuts(false);

		shortcut_manager.update();
		camera_controller->update();
	}

	return 0;
}