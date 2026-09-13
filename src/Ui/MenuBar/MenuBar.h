#pragma once

#include <Ui/MenuBar/Menu.h>

#include <vector>

class MenuBar {
private:
	std::vector<Menu> menus;
public:
	void add_menu(Menu menu);

	void render();
};