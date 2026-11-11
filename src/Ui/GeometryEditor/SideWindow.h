#pragma once

#include <Engine.h>

#include <Ui/GeometryEditor/PropertiesWindow/PropertiesPanel.h>
#include <Ui/GeometryEditor/SceneTree.h>

struct SideWindow {
	PropertiesPanel properties_panel;
	SceneTree scene_tree;

	void render() {
		auto window_size = Engine::get_instance()->get_window_size();
		constexpr Vector2 size = { 250, 0 };
		ImVec2 pos = {window_size.x - size.x, 25};
		ImGui::SetNextWindowPos({ pos });
		ImGui::Begin("PropertiesWindow", nullptr, ImGuiWindowFlags_NoDecoration);
		scene_tree.render();
		properties_panel.render();
		ImGui::End();
	}
};