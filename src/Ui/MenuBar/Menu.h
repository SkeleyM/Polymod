#pragma once

#include <Ui/MenuBar/MenuBarItem.h>

#include <string>
#include <vector>

class Menu {
private:
	std::string name;
	std::vector<MenuBarItem> items;
public:
	Menu(std::string name);

	void add_menu_item(MenuBarItem item);
	std::string get_name();

	void render();
};