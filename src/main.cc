#include <iostream>
#include <Engine.h>
#include <InputManager.h>

#include <ApplicationContext.h>

#include <OrbitalCameraController.h>
#include <GeometryEditor.h>

#include <Init/MainMenuBar.h>
#include <Init/GeometryEditorShortcuts.h>
#include <Init/Toolbar.h>

#include <Ui/Screens/Home/HomeScreen.h>
#include <Ui/UiConstants.h>

#include <Renderer/LineRenderer.h>
#include <Renderer/PointRenderer.h>

#include <nfd.h>

OrbitalCameraController* camera_controller = nullptr;
GeometryWireframeRenderer* wireframe_renderer = nullptr;

std::unique_ptr<MenuBar> main_menu_bar = nullptr;
std::unique_ptr<Polymodel::Screens::HomeScreen> home_screen = nullptr;

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
	auto& app_context = ApplicationContext::get_instance();
	auto& geometry_editor = app_context.get_geometry_editor();

	// If there is no active project show the home screen
	if (app_context.get_project_manager().expired()) {
		home_screen->render(app_context.recent_projects);
	}

	app_context.editor_ui->render();
	geometry_editor.render();
	main_menu_bar->render();
	

	// Check that the mouse hasnt moved much this frame before we click
	if (clicked_this_frame && !is_dragging) {
		geometry_editor.select(input.get_mouse_pos());
	}

	// Render the wireframe of the current geometry
	auto current_geometry = geometry_editor.get_current_geometry();
	if (!current_geometry.expired()) {
		Geometry& geometry = *current_geometry.lock().get();
		SelectedGeometry selection = geometry_editor.get_selection();
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

	// Set style constants
	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = COLOUR_CONST_PRIMARY;
	style.Colors[ImGuiCol_Button] = COLOUR_CONST_FOURTHIARY;

	// Create the application context AFTER initialising the engine
	// Since objects in the ApplicationContext such as UI will depend on engine features
	ApplicationContext& app_context = ApplicationContext::get_instance();
	auto& geometry_editor = app_context.get_geometry_editor();
	auto& project_manager = app_context.get_project_manager();

	home_screen = std::make_unique<Polymodel::Screens::HomeScreen>(
		[](std::filesystem::path path, std::string name) {
			// New project button callback
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto new_project = std::make_shared<Polymodel::Project::ProjectManager>(path, name);
			app_context.set_project_manager(new_project);
		},
		[](std::filesystem::path path) { 
			// Recent project open callback
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto new_project = Polymodel::Project::import_project(path);
			app_context.set_project_manager(new_project);
		}
	);

	// Create all global variables
	wireframe_renderer = new GeometryWireframeRenderer();
	camera_controller = new OrbitalCameraController(&scene.camera);
	main_menu_bar = Polymodel::Init::CreateMenuBar();

	wireframe_renderer->set_edge_size(2.0f);
	wireframe_renderer->set_vertex_size(4.0f);

	// Initialise toolbar
	Toolbar& toolbar = geometry_editor.get_toolbar();
	Polymodel::Init::GeometryEditor::initialise_toolbar(toolbar);

	// Register shortcuts
	auto& shortcut_manager = app_context.shortcut_manager;
	Polymodel::Init::Shortcuts::register_geometry_editor_shortcuts(shortcut_manager);

	// Initialise native_file_dialogue.
	NFD_Init();

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

	NFD_Quit();

	// Ensure singleton destructors are called
	app_context.on_exit();

	return 0;
}