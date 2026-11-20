#pragma once

#include <GeometryEditor.h>
#include <ReferenceImages/ReferenceImage.h>
#include <Ui/Primitives/CreateNewGeometryPanel.h>

#include <optional>
#include <memory>
#include <variant>

enum class SceneTreeObjectType {
	Geometry,
	Image,
};

class SceneTree {
private:
	std::optional<CreateNewGeometryPanel> new_geometry_panel{ std::nullopt };

	void next_tree_node_colour();
	void render_geometry_tree();
	void render_image_tree();
public:
	SceneTree() = default;

	SceneTreeObjectType selection_type;
	std::optional<std::variant<std::shared_ptr<ReferenceImage>, std::shared_ptr<Geometry>>> selection;

	void render();
};