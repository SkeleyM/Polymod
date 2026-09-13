#include <Ui/MenuBar/MenuBar.h>

#include <imgui.h>

void MenuBar::add_menu(Menu menu) {
	this->menus.push_back(menu);
}

void MenuBar::render() {
	ImGui::BeginMainMenuBar();
	
	for (Menu& menu : this->menus) {
		menu.render();
	}

	ImGui::EndMainMenuBar();
}