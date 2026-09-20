#include <Engine.h>

#include <Ui/GeometryEditor/SceneTree.h>
#include <Ui/UiConstants.h>

#include <imgui.h>

SceneTree::SceneTree(GeometryEditor* geometry_editor) {
	this->geometry_editor = geometry_editor;
}

void SceneTree::next_tree_node_colour() {
	static bool colour_a = true;

	if (colour_a) {
		ImGui::PushStyleColor(ImGuiCol_Header, COLOUR_CONST_PRIMARY);
	}
	else {
		ImGui::PushStyleColor(ImGuiCol_Header, COLOUR_CONST_SECONDARY);
	}

	colour_a = !colour_a;
}

void SceneTree::render_geometry_tree() {
	if (!ImGui::CollapsingHeader("Geometry"))
		return;

	auto geometry_manager = this->geometry_editor->get_geometry_manager();
	auto all_geometry = geometry_manager.get_all_geometry();

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 25.0f, 0.0f });
	for (std::shared_ptr<Geometry>& geometry : all_geometry) {
		this->next_tree_node_colour();
		if (ImGui::Selectable(geometry.get()->name.c_str())) {
			this->geometry_editor->set_current_geometry(geometry);
		}
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(all_geometry.size());
}

void SceneTree::render() {
	ImGui::PushStyleColor(ImGuiCol_Button, COLOUR_CONST_FOURTHIARY);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, COLOUR_CONST_SECONDARY);
	ImGui::PushStyleColor(ImGuiCol_Text, COLOUR_CONST_TEXT);

	Vector2 window_size = Engine::get_instance()->get_window_size();

	ImGui::SetNextWindowPos({window_size.x - 300, 20}, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize({ 300, 200 });
	ImGui::Begin("Scene Tree", nullptr, ImGuiWindowFlags_NoSavedSettings);
	this->render_geometry_tree();
	ImGui::End();

	ImGui::PopStyleColor(3);
}