#include <Engine.h>

#include <imgui.h>
#include <Ui/UiConstants.h>

namespace Polymodel::Screens::Home {
	void ShowHomeScreen() {
		Engine* engine = Engine::get_instance();
		auto window_size = engine->get_window_size();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, COLOUR_CONST_PRIMARY);
		ImGui::PushStyleColor(ImGuiCol_Button, COLOUR_CONST_FOURTHIARY);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 50.0f, 50.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);

		ImGui::Begin("Home", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
		ImGui::SetWindowPos({ 0, 0 });
		ImGui::SetWindowSize({ window_size.x, window_size.y });
		ImGui::SetWindowFocus();

		ImGui::SetWindowFontScale(2.0f);
		if (ImGui::Button("New Project", {220.0f, 60.0f})) {

		}
		ImGui::SetWindowFontScale(1.0f);

		ImGui::End();

		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}
}