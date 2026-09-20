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
	GeometryManager geometry_manager;
	std::weak_ptr<Geometry> current_geometry;
	std::optional<OperationArgumentPanel> in_progress_operation_panel;
	Toolbar* toolbar;

	SelectMode select_mode;

	// Maps Geometry pointers to the ID of the corresponding mesh in the scene
	std::unordered_map<std::string, int> geometry_scene_mesh_id_map;

	void select_vertex(Vector3 ray_origin, Vector3 ray_direction);
	void select_edge(Vector3 ray_origin, Vector3 ray_direction);
	void select_face(Vector3 ray_origin, Vector3 ray_direction);

	void refresh_current_geometry_in_scene();
public:
	SelectedGeometry selection;

	GeometryEditor();

	void render();

	void select(Vector2 screen_coordinates);
	void set_current_geometry(std::weak_ptr<Geometry> geometry);
	void begin_operation(OperationArgumentPanel operation_panel);
	void do_operation(AbstractGeometryOperation* geometry_operation);

	void set_select_mode(SelectMode mode);
	SelectMode get_select_mode();

	GeometryManager& get_geometry_manager();
	Toolbar& get_toolbar();
	std::weak_ptr<Geometry> get_current_geometry();

	void on_tool_clicked(ToolbarTool* tool);

	void undo();
	void redo();
};