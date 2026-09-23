#include <Common/test_log.h>

#include <Geometry/Geometry.h>

void create_geometry_with_loop(int amount_of_vertices, int strays) {

}

void test_loops() {
	Geometry basic;

	basic.add_vertex({ 0.0f, 0.0f, 0.0f });
	basic.add_vertex({ 0.0f, 1.0f, 0.0f });
	basic.add_vertex({ 0.0f, 0.0f, 2.0f });

	basic.add_connection(0, 1);
	basic.add_connection(1, 2);
	basic.add_connection(2, 0);
}