#pragma once
#include <AxisGrid.h>
#include <Ui/GeometryEditor/EditorModeSelector.h>
#include <Ui/GeometryEditor/SideWindow.h>

class EditorUI {
private:
	AxisGrid axis_grid;
	SideWindow side_window;
	EditorModeSelector editor_mode_selector;
public:
	void render();
};