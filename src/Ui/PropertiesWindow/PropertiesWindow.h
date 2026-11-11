#pragma once

#include <Ui/PropertiesWindow/PropertiesPanel.h>

struct PropertiesWindow {
	PropertiesPanel properties_panel;

	void render() {
		ImGui::Begin("PropertiesWindow");
		properties_panel.render();
		ImGui::End();
	}
};