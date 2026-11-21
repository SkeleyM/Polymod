#include <EditorUI.h>
#include <ApplicationContext.h>

#include <Engine.h>

void EditorUI::render() {
	Engine* engine = Engine::get_instance();
	auto& scene = engine->get_active_scene();

	auto& app_context = ApplicationContext::get_instance();
	auto& geometry_editor = app_context.get_geometry_editor();
	auto& project = app_context.get_project_manager();
	auto& geometry_manager = project.lock()->get_geometry_manager();

	// set Properties panel transform 
	this->side_window.properties_panel.transform_origin_object = this->side_window.scene_tree.selection_type;
	if (this->side_window.scene_tree.selection.has_value()) {
		switch (this->side_window.scene_tree.selection_type) {
			case (SceneTreeObjectType::Geometry): {
				std::shared_ptr<Geometry> current_geometry = 
					std::get<std::shared_ptr<Geometry>>(this->side_window.scene_tree.selection.value());

				// Set the properties panel transform target
				this->side_window.properties_panel.transform = &current_geometry->transform;
				this->side_window.properties_panel.geometry_name = current_geometry->name;

				break;
			}
			case (SceneTreeObjectType::Image): {
				std::shared_ptr<ReferenceImage> selected_reference_image =
					std::get<std::shared_ptr<ReferenceImage>>(this->side_window.scene_tree.selection.value());

				this->side_window.properties_panel.set_transform(&selected_reference_image->get_mesh()->transform);
				break;
			}
		}
	}
	else {
		this->side_window.properties_panel.set_transform(nullptr);
	}

	this->axis_grid.render(scene.camera);
	this->side_window.render(geometry_manager);
	this->editor_mode_selector.render();
}