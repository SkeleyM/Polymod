#pragma once

#include <Ui/GeometryEditor/PropertiesWindow/PropertiesPanel.h>
#include <Ui/GeometryEditor/SceneTree.h>

struct SideWindow {
	PropertiesPanel properties_panel;
	SceneTree scene_tree;

	void render();
};