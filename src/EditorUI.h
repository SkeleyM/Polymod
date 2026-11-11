#pragma once

#include <ApplicationContext.h>
#include <Engine.h>

#include <AxisGrid.h>
#include <Ui/GeometryEditor/SceneTree.h>
#include <Ui/GeometryEditor/PropertiesWindow/PropertiesWindow.h>
#include <Ui/GeometryEditor/EditorModeSelector.h>
#include <Ui/GeometryEditor/SideWindow.h>
#include <GeometryWireframeRenderer.h>

class EditorUI {
private:
	AxisGrid axis_grid;
	SideWindow side_window;
	EditorModeSelector editor_mode_selector;
public:
	void render() {
		Engine* engine = Engine::get_instance();
		auto& scene = engine->get_active_scene();

		this->axis_grid.render(scene.camera);
		this->side_window.render();
		this->editor_mode_selector.render();
	}
};