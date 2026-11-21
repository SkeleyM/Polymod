#pragma once

#include <Ui/GeometryEditor/SceneTree.h>
#include <GeometryManager.h>

#include <Transform.h>
#include <EMath.h>

#include <imgui.h>
#include <string>


struct PropertiesPanel {
	Transform* transform = nullptr;
	// Store the euler rotation seperately to avoid errors in constant conversion between euler and quaternion
	Vector3 euler_rotation = Vector3(0.0f);

	// Where does the transform originate from? (Geometry, Image, etc.)
	SceneTreeObjectType transform_origin_object;
	std::string geometry_name;

	void set_transform(Transform* transform) {
		this->transform = transform;
		if (transform != nullptr)
			euler_rotation = transform->get_rotation_euler();
	}

	void vector3_component(std::string name, Vector3* vector) {
		ImGui::DragFloat3(name.c_str(), (float*)vector, 0.1f);
	}

	void render(GeometryManager& geometry_manager) {
		ImGui::BeginChild("PropertiesPanel", { 0.0f, 150.0f }, ImGuiChildFlags_Borders);
		if (transform) {
			auto position_before = (*transform).position;
			auto scale_before = (*transform).scale;
			auto rotation_before = euler_rotation;

			vector3_component("Position", &(*transform).position);
			vector3_component("Rotation", &euler_rotation);
			vector3_component("Scale", &(*transform).scale);

			// Only update the mesh on a change
			if (position_before != (*transform).position || 
				scale_before != (*transform).scale || 
				rotation_before != euler_rotation
				) {
				// Set rotation 
				(*transform).set_rotation_euler(euler_rotation);

				if (transform_origin_object == SceneTreeObjectType::Geometry)
					geometry_manager.update_geometry_mesh(geometry_name);
			}
		}
		ImGui::EndChild();
	}
};