#pragma once

#include <GeometryEditor.h>

class SceneTree {
private:
	GeometryEditor* geometry_editor;

	void next_tree_node_colour();

	void render_geometry_tree();
public:
	SceneTree(GeometryEditor* geometry_editor);

	void render();
};