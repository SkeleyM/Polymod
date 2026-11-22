#pragma once

#include <Ui/GeometryEditor/PropertiesWindow/PropertiesPanel.h>

struct PropertiesWindow {
	PropertiesPanel properties_panel;

	void render(GeometryManager& geometry_manager) {
		ImGui::Begin("PropertiesWindow");
		properties_panel.render(geometry_manager);
		ImGui::End();
	}
};