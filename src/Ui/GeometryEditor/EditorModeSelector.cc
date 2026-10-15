#include <ApplicationContext.h>
#include <Engine.h>

#include <Ui/GeometryEditor/EditorModeSelector.h>
#include <Ui/UiConstants.h>

#include <imgui.h>

void EditorModeSelector::render() {
	auto& app_context = ApplicationContext::get_instance();
	auto& geometry_editor = app_context.get_geometry_editor();

	Vector2 window_size = Engine::get_instance()->get_window_size();
	window_size.x = window_size.x - 100 - 300;
	window_size.y = 25;

	ImGui::PushStyleColor(ImGuiCol_Button, COLOUR_CONST_FOURTHIARY);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, COLOUR_CONST_SECONDARY);

	ImGui::SetNextWindowPos({window_size.x, window_size.y});
	ImGui::Begin("EditorModeSelector", nullptr, ImGuiWindowFlags_NoDecoration);

	if (ImGui::Button("V")) {
		geometry_editor.set_select_mode(Select_Vertex);
	}
	ImGui::SameLine();
	if (ImGui::Button("E")) {
		geometry_editor.set_select_mode(Select_Edge);
	}
	ImGui::SameLine();
	if (ImGui::Button("F")) {
		geometry_editor.set_select_mode(Select_Face);
	}

	ImGui::PopStyleColor(2);

	ImGui::End();
}