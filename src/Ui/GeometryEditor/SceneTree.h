#pragma once

#include <GeometryEditor.h>
#include <Ui/Primitives/CreateNewGeometryPanel.h>

#include <memory>
#include <optional>

using namespace PolymodProject;

class SceneTree {
private:
	std::optional<CreateNewGeometryPanel> new_geometry_panel{ std::nullopt };

	void next_tree_node_colour();

	void render_geometry_tree();
public:
	SceneTree() = default;

	void render();
};