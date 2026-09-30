#pragma once

#include <GeometryEditor.h>
#include <Ui/Primitives/CreateNewGeometryPanel.h>

#include <memory>
#include <optional>

class SceneTree {
private:
	GeometryEditor* geometry_editor;
	std::optional<CreateNewGeometryPanel> new_geometry_panel{ std::nullopt };

	void next_tree_node_colour();

	void render_geometry_tree();
public:
	SceneTree(GeometryEditor* geometry_editor);

	void render();
};