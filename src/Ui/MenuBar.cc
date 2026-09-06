#include <Ui/MenuBar.h>

void MenuBar::render() {
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File", true)) {
		ImGui::Text("ah");
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();
}