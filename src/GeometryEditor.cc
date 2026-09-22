#include <GeometryEditor.h>
#include <Geometry/Operations/ExtrudeOperation.h>

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
}

void GeometryEditor::refresh_current_geometry_in_scene() {
	std::string geometry_name = this->current_geometry.lock().get()->name;
	Scene& scene = Engine::get_instance()->get_active_scene();

	scene.remove_mesh(this->geometry_scene_mesh_id_map[geometry_name]);
	auto geometry = this->current_geometry.lock();
	geometry.get()->calculate_normals(SHADE_FLAT);

	// Make copy of current geometry, as we will be changing details for visual feedback
	// Like colouring selection, and we want to avoid making permanent changes
	Geometry copy_of_current = Geometry(*geometry.get());

	// Colour the selected faces
	std::vector<Face>& faces = copy_of_current.get_faces();
	for (int f = 0; f < faces.size(); f++) {
		Face& face = faces[f];
		// If the current face is in the selected faces, colour it differently
		if (
			this->selection.selected_faces != std::nullopt &&
			std::find(
			this->selection.selected_faces.value().begin(), 
			this->selection.selected_faces.value().end(), 
			face
		) != this->selection.selected_faces.value().end()) {
			faces[f].face_colour = { 1.0f, 0.4f, 0.0f };
		}
	}

	Mesh new_mesh = copy_of_current.triangulate();

	this->geometry_scene_mesh_id_map[geometry_name] = new_mesh.id;
	scene.add_mesh(new_mesh);
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
		auto operation = this->in_progress_operation_panel.value().get_operation();

		Geometry present = operation->do_operation();
		*this->current_geometry.lock().get() = present;

		this->refresh_current_geometry_in_scene();

		// Render operation panel
		this->in_progress_operation_panel.value().render();
	}
}

void GeometryEditor::select_vertex(Vector3 ray_origin, Vector3 ray_direction) {
	auto geometry = this->current_geometry.lock().get();

	int closest_vertex_id{ -1 };
	float closest_vertex_distance{ INFINITY };
	for (int vertex_id : geometry->get_all_vertex_ids()) {
		Vertex vertex = geometry->get_vertex(vertex_id);

		float distance{ 0.0f };
		float click_radius = 2.0f;
		bool intersects = glm::intersectRaySphere(ray_origin, ray_direction, vertex.position, click_radius, distance);
		if (intersects && distance < closest_vertex_distance) {
			closest_vertex_id = vertex_id;
			closest_vertex_distance = distance;
		}
	}

	// If we even hit a vertex
	if (closest_vertex_id != -1) {
		SelectedGeometry selection;
		selection.selected_vertices = { closest_vertex_id };
		this->selection = selection;
		this->refresh_current_geometry_in_scene();
	}
}

void GeometryEditor::select_edge(Vector3 ray_origin, Vector3 ray_direction) {

}

void GeometryEditor::select_face(Vector3 ray_origin, Vector3 ray_direction) {
	Vector2 out_barycentric;
	float out_distance;

	// The ray will likely intersect multiple faces, so we only want the closest one
	// as that will be the one on screen,
	Face closest_face = Face({});
	float closest_face_distance = INFINITY;

	// Go through each face and triangulate, then check if our ray intersects the triangle;
	auto geometry = this->current_geometry.lock().get();
	for (Face face : geometry->get_faces()) {
		auto triangulated_face = face.triangulate();
		for (TriangleIds triangle : triangulated_face) {
			Vertex v0 = geometry->get_vertex(triangle.v0);
			Vertex v1 = geometry->get_vertex(triangle.v1);
			Vertex v2 = geometry->get_vertex(triangle.v2);
			bool intersects = glm::intersectRayTriangle(ray_origin,
				ray_direction,
				v0.position, v1.position, v2.position,
				out_barycentric,
				out_distance
			);

			if (intersects && out_distance < closest_face_distance) {
				closest_face = face;
				closest_face_distance = out_distance;
			}
		}
	}
	// If we even hit a single face
	if (closest_face.vertices.size() != 0) {
		SelectedGeometry selection;
		selection.selected_faces = {closest_face};
		this->selection = selection;
		this->refresh_current_geometry_in_scene();
	}
}

void GeometryEditor::select(Vector2 screen_coordinates) {
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

void GeometryEditor::set_current_geometry(std::weak_ptr<Geometry> geometry) {
	this->current_geometry = geometry;
}

void GeometryEditor::begin_operation(OperationArgumentPanel operation_panel) {
	this->in_progress_operation_panel = operation_panel;
}

void GeometryEditor::do_operation(AbstractGeometryOperation* geometry_operation) {
	// Complete operation
	this->in_progress_operation_panel = std::nullopt;
	std::string geometry_name = this->current_geometry.lock().get()->name;
	std::weak_ptr<Timeline> timeline = this->geometry_manager.get_timeline(this->current_geometry);
	timeline.lock().get()->push_operation(std::shared_ptr<AbstractGeometryOperation>(geometry_operation));
	
	// Set current geometry
	Geometry present = timeline.lock().get()->get_present_geometry();
	*this->current_geometry.lock().get() = present;

	this->refresh_current_geometry_in_scene();
}

void GeometryEditor::cancel_operation() {
	// Get input from the operation and restore the geometry
	Geometry restored_geometry = this->in_progress_operation_panel.value().get_operation()->input_geometry;
	*this->current_geometry.lock().get() = restored_geometry;

	this->in_progress_operation_panel = std::nullopt;
	this->refresh_current_geometry_in_scene();
}

void GeometryEditor::set_select_mode(SelectMode mode) {
	this->select_mode = mode;
}

SelectMode GeometryEditor::get_select_mode() {
	return this->select_mode;
}

GeometryManager& GeometryEditor::get_geometry_manager() {
	return this->geometry_manager;
}

Toolbar& GeometryEditor::get_toolbar() {
	return *this->toolbar;
}

std::weak_ptr<Geometry> GeometryEditor::get_current_geometry() {
	return this->current_geometry;
}

void GeometryEditor::undo() {
	Timeline* timeline = this->geometry_manager.get_timeline(this->current_geometry).lock().get();
	if (timeline->get_operations().size() == 0) return;

	timeline->pop_operation();
	Geometry present = timeline->get_present_geometry();

	*this->current_geometry.lock().get() = present;
	this->refresh_current_geometry_in_scene();
}

void GeometryEditor::redo() {
	Timeline* timeline = this->geometry_manager.get_timeline(this->current_geometry).lock().get();
	if (timeline->get_operations().size() == 0) return;
	timeline->forward();
	Geometry present = timeline->get_present_geometry();

	*this->current_geometry.lock().get() = present;
	this->refresh_current_geometry_in_scene();
}