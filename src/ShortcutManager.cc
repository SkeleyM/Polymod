#include <ShortcutManager.h>

#include <iostream>

void ShortcutManager::update() {
    if (!this->should_listen_for_shortcuts)
        return;

    InputManager& input = InputManager::get();
    for (Shortcut& shortcut : this->shortcuts) {
        if (input.get_key_down(shortcut.key) && input.is_modifiers_active(shortcut.modifiers) && shortcut.active && !shortcut.pressed) {
            shortcut.pressed = true;
            shortcut.action();
        } else if (!input.get_key_down(shortcut.key)) {
            shortcut.pressed = false;
        }
    }
}

void ShortcutManager::add_shortcut(Shortcut shortcut) {
    this->shortcuts.push_back(shortcut);
}

void ShortcutManager::ignore_shortcuts(bool ignore) {
    this->should_listen_for_shortcuts = !ignore;
}