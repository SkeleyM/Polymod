#include <Ui/MenuBar/MenuBar.h>
#include <Ui/UiConstants.h>

#include <imgui.h>

void MenuBar::add_menu(Menu menu) {
	this->menus.push_back(menu);
}

void MenuBar::render() {
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, COLOUR_CONST_PRIMARY);
	ImGui::PushStyleColor(ImGuiCol_Text, COLOUR_CONST_TEXT);

	ImGui::BeginMainMenuBar();
	
	for (Menu& menu : this->menus) {
		menu.render();
	}

	ImGui::EndMainMenuBar();

	ImGui::PopStyleColor(2);
}