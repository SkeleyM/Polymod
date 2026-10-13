#include <iostream>
#include <string>

#include <Common/test_log.h>

#include <Geometry_Tests/test_loops.h>
#include <Geometry_Tests/test_raycasting.h>
#include <Geometry_Tests/Format/test_wavefront_obj.h>

int main() {
	test_loops();
	test_raycasts();
	test_wavefront_obj();

	return EXIT_SUCCESS;
}