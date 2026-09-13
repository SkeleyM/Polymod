#include <Ui/MenuBar/Menu.h>

#include <imgui.h>

Menu::Menu(std::string name) {
	this->name = name;
}

void Menu::add_menu_item(MenuBarItem item) {
	this->items.push_back(item);
}

std::string Menu::get_name() {
	return this->name;
}

void Menu::render() {
	if (ImGui::BeginMenu(this->name.c_str(), true)) {
		for (MenuBarItem& item : this->items) {
			item.render();
		}

		ImGui::EndMenu();
	}
}