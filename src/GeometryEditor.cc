#include <GeometryEditor.h>
#include <Geometry/GeometryRaycasting.h>
#include <Geometry/Operations/ExtrudeOperation.h>
#include <Geometry/GeometryPrimitives.h>

#include <Scene.h>
#include <Engine.h>
#include <Renderer/Camera.h>

#include <glm/gtx/intersect.hpp>

GeometryEditor::GeometryEditor() {
	this->toolbar = new Toolbar([&](ToolbarTool* tool) {
		this->on_tool_clicked(tool);
		}
	);
	this->select_mode = Select_Vertex;
	this->selection = SelectedGeometry();

	this->set_select_mode(Select_Face);
}

void GeometryEditor::on_tool_clicked(ToolbarTool* tool) {
	auto panel = tool->create_panel(this, [&](AbstractGeometryOperation* op)  {
		this->do_operation(op);
		}, [&]() {
			this->cancel_operation();
		}
	);
	this->begin_operation(panel);
}

void GeometryEditor::render() {
	this->toolbar->render();

	if (this->in_progress_operation_panel.has_value()) {
		// Perform the operation temporarily
		AbstractGeometryOperation* operation = this->in_progress_operation_panel.value().get_operation();

		Geometry present = operation->do_operation();
		*this->current_geometry.lock().get() = present;

		this->update_mesh_flag = true;

		// Render operation panel
		this->in_progress_operation_panel.value().render();
	}
}

void GeometryEditor::select_vertex(Vector3 ray_origin, Vector3 ray_direction) {
	auto raycast_result = GeometryRaycasting::raycast_vertex(*this->current_geometry.lock().get(), ray_origin, ray_direction);

	// If we even hit a single face
	if (raycast_result.has_value()) {
		SelectedGeometry selection;
		selection.selected_vertices = { raycast_result.value() };
		this->selection = selection;
		this->update_mesh_flag = true;
	}
}

void GeometryEditor::select_edge(Vector3 ray_origin, Vector3 ray_direction) {
	auto raycast_result = GeometryRaycasting::raycast_edge(*this->current_geometry.lock().get(), ray_origin, ray_direction);

	// If we even hit a single face
	if (raycast_result.has_value()) {
		SelectedGeometry selection;
		selection.selected_edges = { raycast_result.value() };
		this->selection = selection;
		this->update_mesh_flag = true;
	}
}

void GeometryEditor::select_face(Vector3 ray_origin, Vector3 ray_direction) {
	auto raycast_result = GeometryRaycasting::raycast_face(*this->current_geometry.lock().get(), ray_origin, ray_direction);

	// If we even hit a single face
	if (raycast_result.has_value()) {
		SelectedGeometry selection;
		selection.selected_faces = {raycast_result.value()};
		this->selection = selection;
		this->update_mesh_flag = true;
	}
}

void GeometryEditor::select(Vector2 screen_coordinates) {
	if (this->current_geometry.expired())
		return;

	// Selection occurs from the prespective of the camera
	Camera camera = Engine::get_instance()->get_active_scene().camera;

	auto inv_proj = glm::inverse(camera.get_projection_matrix());
	auto inv_view = glm::inverse(camera.get_view_matrix());

	Vector2 screen_size = Engine::get_instance()->get_window_size();
	Vector2 ndc_coordinates = {
		((screen_coordinates.x / screen_size.x) * 2) - 1,
		1 - ((screen_coordinates.y / screen_size.y) * 2)
	};

	auto view_space = Vector4(ndc_coordinates, -1, 1) * inv_proj;
	view_space.z = -1;
	view_space.w = 0;

	auto world = view_space * inv_view;

	Vector3 ray_origin = camera.transform.position;
	Vector3 ray_direction = glm::normalize(world);

	switch (this->select_mode) {
		case (Select_Vertex): {
			this->select_vertex(ray_origin, ray_direction);
			break;
		}
		case (Select_Edge): {
			this->select_edge(ray_origin, ray_direction);
			break;
		}
		case (Select_Face): {
			this->select_face(ray_origin, ray_direction);
			break;
		}
	}
}

void GeometryEditor::set_current_geometry(std::weak_ptr<Geometry> geometry, std::weak_ptr<Timeline> timeline) {
	this->current_geometry = geometry;
	this->current_geometry_timeline = timeline;
	this->set_selection({});

	// Reset flags
	this->geometry_change_flag = false;
	this->update_mesh_flag = false;
}

void GeometryEditor::begin_operation(OperationArgumentPanel operation_panel) {
	this->in_progress_operation_panel = operation_panel;
}

void GeometryEditor::do_operation(AbstractGeometryOperation* geometry_operation) {
	// Complete operation
	this->in_progress_operation_panel = std::nullopt;
	std::string geometry_name = this->current_geometry.lock().get()->name;
	this->current_geometry_timeline.lock().get()->push_operation(std::shared_ptr<AbstractGeometryOperation>(geometry_operation));
	
	// Set current geometry
	Geometry present = this->current_geometry_timeline.lock().get()->get_present_geometry();
	*this->current_geometry.lock().get() = present;

	this->geometry_change_flag = true;
	this->update_mesh_flag = true;
}

void GeometryEditor::cancel_operation() {
	if (!this->in_progress_operation_panel.has_value())
		return;

	// Get input from the operation and restore the geometry
	Geometry restored_geometry = this->in_progress_operation_panel.value().get_operation()->input_geometry;
	*this->current_geometry.lock().get() = restored_geometry;

	this->in_progress_operation_panel = std::nullopt;
	this->update_mesh_flag = true;
}

bool GeometryEditor::is_performing_operation() {
	return this->in_progress_operation_panel.has_value();
}

bool GeometryEditor::has_geometry_changed() {
	return this->geometry_change_flag;
}

void GeometryEditor::reset_geometry_change_flag() {
	this->geometry_change_flag = false;
}

bool GeometryEditor::should_mesh_be_updated() {
	return this->update_mesh_flag;
}

void GeometryEditor::reset_mesh_update_flag() {
	this->update_mesh_flag = false;
}

void GeometryEditor::set_select_mode(SelectMode mode) {
	this->select_mode = mode;
}

SelectMode GeometryEditor::get_select_mode() {
	return this->select_mode;
}

void GeometryEditor::set_selection(SelectedGeometry selection) {
	this->selection = selection;
	this->update_mesh_flag = true;
}

SelectedGeometry GeometryEditor::get_selection() {
	return this->selection;
}

Toolbar& GeometryEditor::get_toolbar() {
	return *this->toolbar;
}

std::weak_ptr<Geometry> GeometryEditor::get_current_geometry() {
	return this->current_geometry;
}

void GeometryEditor::undo() {
	Timeline* timeline = this->current_geometry_timeline.lock().get();
	if (timeline->get_operations().size() == 0) return;

	timeline->pop_operation();
	Geometry present = timeline->get_present_geometry();

	*this->current_geometry.lock().get() = present;
	this->update_mesh_flag = true;
	this->geometry_change_flag = true;
}

void GeometryEditor::redo() {
	Timeline* timeline = this->current_geometry_timeline.lock().get();
	if (timeline->get_operations().size() == 0) return;
	timeline->forward();
	Geometry present = timeline->get_present_geometry();

	*this->current_geometry.lock().get() = present;
	this->update_mesh_flag = true;
	this->geometry_change_flag = true;
}