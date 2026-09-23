#include <Common/test_log.h>

#include <Geometry/Geometry.h>

Geometry create_geometry_with_loop(int amount_of_vertices, int strays) {
	Geometry geometry;

	for (int i = 0; i < amount_of_vertices; i++) {
		geometry.add_vertex({ (float)i, 0.0f, 0.0f });
	}

	for (int i = 0; i < amount_of_vertices; i++) {
		geometry.add_connection(i, (i + 1) % amount_of_vertices);
	}

	return geometry;
}

void test_perfect_loop() {
	bool result = true;
	for (int i = 0; i < 5; i++) {
		Geometry geometry = create_geometry_with_loop(5 + i, 0);
		auto loop = geometry.get_loop(geometry.get_all_vertex_ids());
		result |= loop.has_value();
	}
	ASSERT_TRUE(result);
}

void test_not_a_loop() {
	bool result = false;
	for (int i = 0; i < 5; i++) {
		Geometry geometry = create_geometry_with_loop(5 + i, 0);

		// Add an extra vertex that is not connected to the loop, and include it in the loop search
		geometry.add_vertex({ 0.0f, 0.0f, 0.0f });
		auto ids = geometry.get_all_vertex_ids();
		ids.push_back(i + 6);
		auto loop = geometry.get_loop(ids);
		result |= loop.has_value();
	}
	ASSERT_FALSE(result);
}

void test_loops() {
	test_perfect_loop();
	test_not_a_loop();
}