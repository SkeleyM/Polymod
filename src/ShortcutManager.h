#pragma once

#include <InputManager.h>

#include <vector>
#include <functional>

typedef struct Shortcut {
    int key = 0;
    int modifiers = 0;
    std::function<void()> action = 0;
    bool active = 0;
    bool pressed = 0;
} Shortcut;

class ShortcutManager {
private:
    std::vector<Shortcut> shortcuts;
public:
    void update();
    void add_shortcut(Shortcut shortcut);
};