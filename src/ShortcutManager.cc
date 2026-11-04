#include <ShortcutManager.h>

#include <iostream>

void ShortcutManager::update() {
    if (!this->should_listen_for_shortcuts)
        return;

    InputManager& input = InputManager::get();
    for (Shortcut& shortcut : this->shortcuts) {
        if (input.get_key_down(shortcut.key) && input.is_modifiers_active(shortcut.modifiers) && shortcut.active) {
            if (!shortcut.pressed)
                shortcut.action();

            shortcut.pressed = true;

            // Return on shortcut
            return;
        } else if (!input.get_key_down(shortcut.key)) {
            shortcut.pressed = false;
        }
    }
}

void ShortcutManager::add_shortcut(Shortcut shortcut) {
    // TODO: Proper ordering logic
    // Hacky fix to put shortcuts with modifiers to be prioritised
    if (shortcut.modifiers != KeyModifiers::MODIFIER_NONE)
        this->shortcuts.insert(this->shortcuts.begin(), shortcut);
    else
        this->shortcuts.push_back(shortcut);
}

void ShortcutManager::ignore_shortcuts(bool ignore) {
    this->should_listen_for_shortcuts = !ignore;
}