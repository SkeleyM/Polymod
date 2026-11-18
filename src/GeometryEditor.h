#pragma once

#include <GeometryManager.h>
#include <Ui/OperationArgumentPanel.h>
#include <Ui/Toolbar.h>

enum SelectMode {
	Select_Vertex,
	Select_Edge,
	Select_Face
};

class GeometryEditor {
private:
	std::weak_ptr<Geometry> current_geometry;
	std::weak_ptr<Timeline> current_geometry_timeline;

	// For changes that result in a geometry change
	// Used to represent permanent changes to the geometry
	// Operations, movements, etc.
	bool geometry_change_flag{ false };
	// For changes that result in a render change
	// Used to represent when a non permanent change has occured and should be updated in the scene
	// such as when an operation is being performed and the geometry is being previewed
	// however permanent changes will also set this flag.
	bool update_mesh_flag{ false };

	std::optional<OperationArgumentPanel> in_progress_operation_panel;
	Toolbar* toolbar;

	SelectMode select_mode;
	SelectedGeometry selection;

	void select_vertex(Vector3 ray_origin, Vector3 ray_direction);
	void select_edge(Vector3 ray_origin, Vector3 ray_direction);
	void select_face(Vector3 ray_origin, Vector3 ray_direction);
public:
	GeometryEditor();

	void render();

	void select(Vector2 screen_coordinates);
	void set_current_geometry(std::weak_ptr<Geometry> geometry, std::weak_ptr<Timeline> timeline);
	void begin_operation(OperationArgumentPanel operation_panel);
	void do_operation(AbstractGeometryOperation* geometry_operation);
	void cancel_operation();
	bool is_performing_operation();

	// Flag getters and setters
	bool has_geometry_changed();
	void reset_geometry_change_flag();
	bool should_mesh_be_updated();
	void reset_mesh_update_flag();

	void set_select_mode(SelectMode mode);
	SelectMode get_select_mode();
	void set_selection(SelectedGeometry selection);
	SelectedGeometry get_selection();

	Toolbar& get_toolbar();
	std::weak_ptr<Geometry> get_current_geometry();

	void on_tool_clicked(ToolbarTool* tool);

	void undo();
	void redo();
};