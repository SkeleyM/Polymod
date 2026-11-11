#include <EditorUI.h>
#include <ApplicationContext.h>

#include <Engine.h>

void EditorUI::render() {
	Engine* engine = Engine::get_instance();
	auto& scene = engine->get_active_scene();

	auto& app_context = ApplicationContext::get_instance();
	auto& geometry_editor = app_context.get_geometry_editor();
	auto current_geometry_weak = geometry_editor.get_current_geometry();

	if (!current_geometry_weak.expired()) {
		auto current_geometry = current_geometry_weak.lock();
		// Set the transform of the 
		side_window.properties_panel.transform = &current_geometry.get()->transform;
	}

	this->axis_grid.render(scene.camera);
	this->side_window.render();
	this->editor_mode_selector.render();
}