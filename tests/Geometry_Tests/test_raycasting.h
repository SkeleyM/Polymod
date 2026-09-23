#include <Common/test_log.h>

#include <Geometry/Geometry.h>
#include <Geometry/GeometryRaycasting.h>

#include <vector>

void create_vertex_data(Geometry& geometry, std::vector<Vector3>* ray_origins, std::vector<Vector3>* ray_directions, int amount) {
	for (int i = 0; i < amount; i++) {
		Vector3 vertex(std::rand(), std::rand(), std::rand());
		Vector3 origin(std::rand(), std::rand(), std::rand());
		Vector3 ray_dir = glm::normalize(origin - vertex);

		geometry.add_vertex(vertex);
		ray_origins->push_back(origin);
		ray_directions->push_back(ray_dir);
	}
	
}

void test_vertex_raycasts() {
	Geometry geometry;
	std::vector<Vector3> ray_origins;
	std::vector<Vector3> ray_directions;

	const int amount = 15;
	create_vertex_data(geometry, &ray_origins, &ray_directions, amount);

	bool test_result = false;
	for (int i = 0; i < amount; i++) {
		auto raycast = GeometryRaycasting::raycast_vertex(geometry, ray_origins[i], ray_directions[i]);
		test_result |= !raycast.has_value();
	}
	ASSERT_TRUE(test_result);
}

void test_vertex_raycasts_should_miss() {
	Geometry geometry;
	std::vector<Vector3> ray_origins;
	std::vector<Vector3> ray_directions;

	const int amount = 15;
	create_vertex_data(geometry, &ray_origins, &ray_directions, amount);

	bool test_result = false;
	for (int i = 0; i < amount; i++) {
		auto raycast = GeometryRaycasting::raycast_vertex(geometry, ray_origins[i], -ray_directions[i]);
		test_result |= raycast.has_value();
	}
	ASSERT_FALSE(test_result);
}

void test_raycasts() {
	test_vertex_raycasts();
	test_vertex_raycasts_should_miss();
}