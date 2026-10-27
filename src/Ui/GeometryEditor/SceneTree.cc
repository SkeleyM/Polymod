#include <Engine.h>

#include <ApplicationContext.h>

#include <Ui/GeometryEditor/SceneTree.h>
#include <Ui/UiConstants.h>

#include <Ui/Primitives/PrimitiveOperationPanels.h>

#include <imgui.h>

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

	auto& app_context = ApplicationContext::get_instance();
	auto& geometry_manager = app_context.get_project_manager().lock()->get_geometry_manager();
	auto& geometry_editor = app_context.get_geometry_editor();

	auto all_geometry = geometry_manager.get_all_geometry();

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 25.0f, 0.0f });
	for (std::shared_ptr<Geometry>& geometry : all_geometry) {
		this->next_tree_node_colour();
		if (ImGui::Selectable(geometry.get()->name.c_str())) {
			auto timeline = geometry_manager.get_timeline(geometry);
			geometry_editor.set_current_geometry(geometry, timeline);
		}
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(all_geometry.size());
}

void SceneTree::render() {
	auto& app_context = ApplicationContext::get_instance();
	// If there is no active project
	if (app_context.get_project_manager().expired())
		return;

	auto& geometry_manager = app_context.get_project_manager().lock()->get_geometry_manager();
	auto& geometry_editor = app_context.get_geometry_editor();


	ImGui::PushStyleColor(ImGuiCol_Button, COLOUR_CONST_FOURTHIARY);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, COLOUR_CONST_SECONDARY);
	ImGui::PushStyleColor(ImGuiCol_Text, COLOUR_CONST_TEXT);

	Vector2 window_size = Engine::get_instance()->get_window_size();

	ImGui::SetNextWindowPos({window_size.x - 300, 20}, ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize({ 300, 200 });
	ImGui::Begin("Scene Tree", nullptr, ImGuiWindowFlags_NoSavedSettings);
	if (ImGui::Button("New")) {
		this->new_geometry_panel = CreateNewGeometryPanel();
	}

	if (this->new_geometry_panel) {
		this->new_geometry_panel->render();
	}
	// If the panel is completed then it has created the new geometry;
	// and can be destroyed
	if (this->new_geometry_panel != std::nullopt && this->new_geometry_panel->completed) {
		auto new_geometry = geometry_manager.create_new_geometry(this->new_geometry_panel->get_name());
		geometry_editor.set_current_geometry(new_geometry, geometry_manager.get_timeline(new_geometry));
		geometry_editor.on_tool_clicked(new CreatePrimitiveTool(this->new_geometry_panel->get_primitive()));
		this->new_geometry_panel = std::nullopt;
	}

	this->render_geometry_tree();
	ImGui::End();

	ImGui::PopStyleColor(3);
}