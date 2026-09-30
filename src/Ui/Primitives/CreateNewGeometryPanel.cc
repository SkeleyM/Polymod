#include <Ui/Primitives/CreateNewGeometryPanel.h>
#include <Engine.h>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

CreateNewGeometryPanel::CreateNewGeometryPanel() {
	Engine* engine = Engine::get_instance();
	Vector2 screen_pos = engine->get_window_size() / 2.0f;
	this->primitiveSelector = PrimitiveSelector(screen_pos);
}

CreateNewGeometryPanel::~CreateNewGeometryPanel() {
}

GeometryPrimitives::GeometryPrimitive CreateNewGeometryPanel::get_primitive() {
	return this->primitiveSelector.get_primitive();
}

void CreateNewGeometryPanel::render() {
	ImGui::Begin("Create Geometry");
	ImGui::InputText("Name", &this->new_geometry_name_buffer);


	if (ImGui::Button("Next")) {
		this->name_set = true;
	}

	if (this->name_set) {
		this->primitiveSelector.render();
	}

	if (this->primitiveSelector.selection_ready()) {
		this->completed = true;
	}
	 
	ImGui::End();
}