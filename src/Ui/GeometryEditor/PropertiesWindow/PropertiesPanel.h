#pragma once

#include <Transform.h>
#include <EMath.h>

#include <imgui.h>
#include <string>


struct PropertiesPanel {
	Transform* transform = nullptr;

	void vector3_component(std::string name, Vector3* vector) {
		ImGui::DragFloat3(name.c_str(), (float*)vector, 0.1f);
	}

	void render() {
		ImGui::BeginChild("PropertiesPanel", { 0.0f, 150.0f }, ImGuiChildFlags_Borders);
		if (transform) {
			vector3_component("Position", &(*transform).position);
			vector3_component("Scale", &(*transform).scale);
		}
		ImGui::EndChild();
	}
};