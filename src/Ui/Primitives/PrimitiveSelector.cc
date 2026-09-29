#include <Ui/Primitives/PrimitiveSelector.h>

#include <imgui.h>

PrimitiveSelector::PrimitiveSelector(GeometryEditor* editor, Vector2 screen_position) {
	this->editor = editor;
	this->screen_position = screen_position;
}

void PrimitiveSelector::set_screen_position(Vector2 screen_position) {
	this->screen_position = screen_position;
}

void PrimitiveSelector::render() {
	ImGui::SetNextWindowSize({ 100, 250 });
	ImGui::Begin("PrimitiveSelector", nullptr, ImGuiWindowFlags_NoDecoration);
	if (ImGui::Button("Cube")) {

	}
	if (ImGui::Button("Cylinder")) {

	}
	if (ImGui::Button("Uv Sphere")) {

	}
	if (ImGui::Button("Torus")) {

	}
	if (ImGui::Button("Circle")) {

	}
	if (ImGui::Button("Plane")) {

	}
	if (ImGui::Button("Vertex")) {

	}
	ImGui::End();
}