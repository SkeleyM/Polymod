#pragma once

#include <ApplicationContext.h>
#include <ShortcutManager.h>

#include <Init/InitCommonFunc.h>

namespace Polymodel::Init::Shortcuts {
	void register_project_shortcuts(ShortcutManager& shortcut_manager) {
		shortcut_manager.add_shortcut({ GLFW_KEY_S, MODIFIER_CONTROL, []() {
			Polymodel::Init::CommonFuncs::save_active_project();
		}, true });
	}
}