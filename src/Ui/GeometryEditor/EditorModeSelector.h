#pragma once

#include <GeometryEditor.h>

class EditorModeSelector {
private:
	GeometryEditor* geometry_editor;
public:
	EditorModeSelector(GeometryEditor* geometry_editor);

	void render();
};