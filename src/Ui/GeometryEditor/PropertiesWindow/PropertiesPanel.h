#pragma once

#include <Ui/GeometryEditor/SceneTree.h>
#include <GeometryManager.h>

#include <Transform.h>
#include <EMath.h>

#include <imgui.h>
#include <string>


struct PropertiesPanel {
	Transform* transform = nullptr;
	// Where does the transform originate from? (Geometry, Image, etc.)
	SceneTreeObjectType transform_origin_object;
	std::string geometry_name;

	void vector3_component(std::string name, Vector3* vector) {
		ImGui::DragFloat3(name.c_str(), (float*)vector, 0.1f);
	}

	void render(GeometryManager& geometry_manager) {
		ImGui::BeginChild("PropertiesPanel", { 0.0f, 150.0f }, ImGuiChildFlags_Borders);
		if (transform) {
			auto position_before = (*transform).position;
			auto scale_before = (*transform).scale;

			vector3_component("Position", &(*transform).position);
			vector3_component("Scale", &(*transform).scale);

			// Only update the mesh on a change
			if (position_before != (*transform).position || scale_before != (*transform).scale) {
				if (transform_origin_object == SceneTreeObjectType::Geometry)
					geometry_manager.update_geometry_mesh(geometry_name);
			}
		}
		ImGui::EndChild();
	}
};