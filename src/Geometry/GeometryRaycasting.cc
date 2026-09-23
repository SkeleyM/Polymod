#include <Geometry/GeometryRaycasting.h>

#include <glm/gtx/intersect.hpp>

std::optional<Face> GeometryRaycasting::raycast_face(Geometry& geometry, Vector3 ray_origin, Vector3 ray_direction) {
	Vector2 out_barycentric;
	float out_distance;

	// The ray will likely intersect multiple faces, so we only want the closest one
	// as that will be the one on screen,
	Face closest_face = Face({});
	float closest_face_distance = INFINITY;

	// Go through each face and triangulate, then check if our ray intersects the triangle;
	for (Face face : geometry.get_faces()) {
		auto triangulated_face = face.triangulate();
		for (TriangleIds triangle : triangulated_face) {
			Vertex v0 = geometry.get_vertex(triangle.v0);
			Vertex v1 = geometry.get_vertex(triangle.v1);
			Vertex v2 = geometry.get_vertex(triangle.v2);
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
		return closest_face;
	}

	return std::nullopt;
}

std::optional<std::pair<int, int>> GeometryRaycasting::raycast_edge(Geometry& geometry, Vector3 ray_origin, Vector3 ray_direction) {
	return std::nullopt;
}

std::optional<int> GeometryRaycasting::raycast_vertex(Geometry& geometry, Vector3 ray_origin, Vector3 ray_direction) {
	int closest_vertex_id{ -1 };
	float closest_vertex_distance{ INFINITY };
	for (int vertex_id : geometry.get_all_vertex_ids()) {
		Vertex vertex = geometry.get_vertex(vertex_id);

		if (glm::dot(ray_direction, glm::normalize(ray_origin - vertex.position)) < 0.0f) {
			continue;
		}

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
		return closest_vertex_id;
	}

	return std::nullopt;
}