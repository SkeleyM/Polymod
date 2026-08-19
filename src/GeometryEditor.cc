#include <GeometryEditor.h>
#include <Geometry/Operations/ExtrudeOperation.h>

#include <Scene.h>
#include <Engine.h>
#include <Renderer/Camera.h>

#include <glm/gtx/intersect.hpp>

#include <iostream>

GeometryEditor::GeometryEditor() {
	this->toolbar = new Toolbar([&](ToolbarTool* tool) {
		this->on_tool_clicked(tool);
		}
	);
	this->select_mode = Select_Vertex;
	this->selection = SelectedGeometry();
}

void GeometryEditor::on_tool_clicked(ToolbarTool* tool) {
	auto panel = tool->create_panel(this, [&](AbstractGeometryOperation* op)  {
		this->do_operation(op);
		}
	);
	this->begin_operation(panel);
}

void GeometryEditor::render() {
	this->toolbar->render();

	if (this->in_progress_operation_panel.has_value()) {
		std::string geometry_name = this->current_geometry.lock().get()->name;
		Scene& scene = Engine::get_instance()->get_active_scene();

		// Perform the operation temporarily
		auto operation = this->in_progress_operation_panel.value().get_operation();
		std::weak_ptr<Timeline> timeline = this->geometry_manager.get_timeline(this->current_geometry);
		timeline.lock().get()->push_operation(std::shared_ptr<AbstractGeometryOperation>(operation));
		scene.remove_mesh(this->geometry_scene_mesh_id_map[geometry_name]);

		Geometry present = timeline.lock().get()->get_present_geometry();
		*this->current_geometry.lock().get() = present;

		auto current_geometry = this->current_geometry.lock();
		current_geometry.get()->calculate_normals(SHADE_FLAT);
		Mesh new_mesh = current_geometry.get()->triangulate();

		this->geometry_scene_mesh_id_map[geometry_name] = new_mesh.id;
		scene.add_mesh(new_mesh);

		// Render operation panel
		this->in_progress_operation_panel.value().render();
	}
}

void GeometryEditor::select_vertex(Vector2 screen_coordinates) {

}

void GeometryEditor::select_edge(Vector2 screen_coordinates) {

}

void GeometryEditor::select_face(Vector2 screen_coordinates) {
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
		selection.selected_faces = std::vector<Face>();
		this->selection = selection;
		this->selection.selected_faces->clear();
		this->selection.selected_faces->push_back(closest_face);
		
	}
}

void GeometryEditor::select(Vector2 screen_coordinates) {
	switch (this->select_mode) {
		case (Select_Vertex): {
			this->select_vertex(screen_coordinates);
			break;
		}
		case (Select_Edge): {
			this->select_edge(screen_coordinates);
			break;
		}
		case (Select_Face): {
			this->select_face(screen_coordinates);
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
	this->in_progress_operation_panel = std::nullopt;
	std::string geometry_name = this->current_geometry.lock().get()->name;

	// Remove the current geometry from the scene
	Scene& scene = Engine::get_instance()->get_active_scene();
	scene.remove_mesh(this->geometry_scene_mesh_id_map[geometry_name]);

	std::weak_ptr<Timeline> timeline = this->geometry_manager.get_timeline(this->current_geometry);
	timeline.lock().get()->push_operation(std::shared_ptr<AbstractGeometryOperation>(geometry_operation));

	Geometry present = timeline.lock().get()->get_present_geometry();
	*this->current_geometry.lock().get() = present;

	// Add new geometry to scene to be rendered
	auto current_geometry = this->current_geometry.lock();
	current_geometry.get()->calculate_normals(SHADE_FLAT);
	Mesh new_mesh = current_geometry.get()->triangulate();
	this->geometry_scene_mesh_id_map[geometry_name] = new_mesh.id;
	scene.add_mesh(new_mesh);
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