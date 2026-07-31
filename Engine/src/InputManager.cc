#include <InputManager.h>

InputManager* InputManager::instance = nullptr;

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

Vector2 InputManager::get_scroll() {
	return this->scroll_delta;
}

Vector2 InputManager::get_mouse_pos() {
	return this->mouse_pos;
}

bool InputManager::get_key_down(int key) {
	return this->keyboard_state[key];
}

void InputManager::_set_scroll_delta(Vector2 delta) {
	this->scroll_delta = delta;
}

void InputManager::_set_mouse_pos(Vector2 pos) {
	this->mouse_pos = pos;
}

void InputManager::_set_keyboard_state(int key, bool pressed) {
	this->keyboard_state[key] = pressed;
}

void InputManager::_reset_scroll() {
	this->scroll_delta = Vector2();
}