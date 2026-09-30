#include <Ui/Primitives/PrimitiveSelector.h>

#include <imgui.h>

PrimitiveSelector::PrimitiveSelector() {
	this->screen_position = { 0.0f, 0.0f };
}

PrimitiveSelector::PrimitiveSelector(Vector2 screen_position) {
	this->screen_position = screen_position;
}

void PrimitiveSelector::set_screen_position(Vector2 screen_position) {
	this->screen_position = screen_position;
}

bool PrimitiveSelector::selection_ready() {
	return this->is_selection_ready;
}

GeometryPrimitives::GeometryPrimitive PrimitiveSelector::get_primitive() {
	return this->primitive;
}

void PrimitiveSelector::render() {
	ImGui::SetNextWindowSize({ 100, 250 });
	ImGui::Begin("PrimitiveSelector", nullptr, ImGuiWindowFlags_NoDecoration);
	if (ImGui::Button("Cube")) {
		this->primitive = GeometryPrimitives::Cube;
		this->is_selection_ready = true;
	}
	if (ImGui::Button("Cylinder")) {
		this->primitive = GeometryPrimitives::Cylinder;
		this->is_selection_ready = true;
	}
	if (ImGui::Button("Uv Sphere")) {
		this->primitive = GeometryPrimitives::Sphere_Uv;
		this->is_selection_ready = true;
	}
	if (ImGui::Button("Torus")) {
		this->primitive = GeometryPrimitives::Torus;
		this->is_selection_ready = true;
	}
	if (ImGui::Button("Circle")) {
		this->primitive = GeometryPrimitives::Circle;
		this->is_selection_ready = true;
	}
	if (ImGui::Button("Plane")) {
		this->primitive = GeometryPrimitives::Plane;
		this->is_selection_ready = true;
	}
	if (ImGui::Button("Vertex")) {
		this->primitive = GeometryPrimitives::Vertex;
		this->is_selection_ready = true;
	}
	ImGui::End();
}