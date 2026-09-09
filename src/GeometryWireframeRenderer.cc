#include <GeometryWireframeRenderer.h>

void GeometryWireframeRenderer::set_edge_size(float size) {
    this->edge_renderer.set_line_width(size);
}

void GeometryWireframeRenderer::set_vertex_size(float size) {
    this->vertex_renderer.set_point_size(size);
}

void GeometryWireframeRenderer::render_wireframe(Geometry& geometry, SelectedGeometry& highlight_selection) {
	// Render the wireframe of the mesh
	auto all_vertex_id = geometry.get_all_vertex_ids();
	std::vector<Point> points;
	for (int i = 0; i < all_vertex_id.size(); i++) {
		int current_vertex_id = all_vertex_id[i];
		Vector3 vertex_colour = {0.0f, 0.0f, 0.0f};

		// Check if current vertex is selected
		if (highlight_selection.selected_vertices.has_value()){
			auto selected_vertices = highlight_selection.selected_vertices.value();
			if (std::find(selected_vertices.begin(), selected_vertices.end(), current_vertex_id) != selected_vertices.end()) {
				vertex_colour = Vector3(1.0f, 0.4f, 0.0f);
			}
		}

		Vertex vertex = geometry.get_vertex(current_vertex_id);
		Point point = {
			vertex.position,
			vertex_colour
		};
		points.push_back(point);
	}
	
	// Collect all the edges
	std::vector<Line> edges;
	std::vector<std::set<int>> visited;
	for (int i = 0; i < all_vertex_id.size(); i++) {
		Vector3 edge_colour = {0.0f, 0.0f, 0.0f};
		// Check every neighbour
		int current_vertex_id = all_vertex_id[i];
		auto neighbour_ids = geometry.get_neighbours(current_vertex_id);
		for (int id : neighbour_ids) {
			// If we havent visited this pair yet
			if (std::find(visited.begin(), visited.end(), std::set<int>({current_vertex_id, i})) == visited.end()) {
				Vertex v1 = geometry.get_vertex(i);
				Vertex v2 = geometry.get_vertex(id);
				Line edge = {
					v1.position,
					v2.position,
					edge_colour,
				};
				edges.push_back(edge);
			}
		}
	}

	// Render all the vertices
	this->vertex_renderer.render_points(points);
	this->edge_renderer.render_lines(edges);
}

