#include <Ui/MenuBarItem.h>
#include <imgui.h>

MenuBarItem::MenuBarItem(std::string text, std::function<void()> action) {
	this->text = text;
	this->action = action;
}

void MenuBarItem::render() {
	if (ImGui::MenuItem(text.c_str(), NULL, nullptr, this->enabled)) {
		action();
	}
}

void MenuBarItem::enable() {
	this->enabled = true;
}

void MenuBarItem::disable() {
	this->enabled = false;
}