#pragma once
#include <functional>
#include <string>

class MenuBarItem {
private:
	std::string text;
	std::function<void()> action;
	bool enabled;
public:
	MenuBarItem(std::string text, std::function<void()> action);
	void render();
	void enable();
	void disable();
};