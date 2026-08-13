// Input manager for glfw
#pragma once
#include <EMath.h>

#include <GLFW/glfw3.h>
#include <iostream>

class InputManager {
private:
	static InputManager* instance;

	InputManager();
	~InputManager();

	Vector2 scroll_delta { 0.0f, 0.0f };
	Vector2 mouse_pos { 0.0f, 0.0f };

	bool mouse_1;
	bool mouse_2;

	// 400 is chosen very arbitrarily, glfw keycodes seem to max out at around ~360
	int keyboard_state[400]{ 0 };
public:
	static InputManager& get() {
		if (instance == nullptr) {
			auto instance = new InputManager();
			InputManager::instance = instance;
			return InputManager::get();
		}

		return *InputManager::instance;
	}

	Vector2 get_scroll();
	Vector2 get_mouse_pos();
	std::pair<bool, bool> get_mouse_buttons();

	bool get_key_down(int key);
	
	void _set_scroll_delta(Vector2 delta);
	void _set_mouse_pos(Vector2 pos);
	void _set_mouse_button(bool mouse_1, bool mouse_2);

	void _set_keyboard_state(int key, bool pressed);

	void _reset_scroll();
};

// GLFW input handlers
static void glfw_scroll_handler(GLFWwindow* win, double dx, double dy) {
	InputManager& input = InputManager::get();
	input._set_scroll_delta(Vector2(dx, dy));
}

static void glfw_mouse_handler(GLFWwindow* win, double x, double y) {
	InputManager& input = InputManager::get();

	Vector2 new_pos = Vector2(x, y);
	input._set_mouse_pos(new_pos);
}

static void glfw_mouse_click_handler(GLFWwindow* window, int button, int action, int mods) {
	InputManager& input = InputManager::get();

	auto current_state = input.get_mouse_buttons();
	if (button == GLFW_MOUSE_BUTTON_1) {
		input._set_mouse_button(action, current_state.second);
	}
	else if (button == GLFW_MOUSE_BUTTON_2) {
		input._set_mouse_button(current_state.first, action);
	}
}

static void glfw_key_handler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	InputManager& input = InputManager::get();
	input._set_keyboard_state(key, action == GLFW_PRESS ? true : false);
}