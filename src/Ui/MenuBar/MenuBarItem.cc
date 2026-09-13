#include <Ui/MenuBar/MenuBarItem.h>
#include <imgui.h>

MenuBarItem::MenuBarItem(std::string name, std::function<void()> action) {
	this->name = name;
	this->action = action;
}

void MenuBarItem::render() {
	if (ImGui::MenuItem(name.c_str(), NULL, nullptr, this->enabled)) {
		action();
	}
}

void MenuBarItem::enable() {
	this->enabled = true;
}

void MenuBarItem::disable() {
	this->enabled = false;
}