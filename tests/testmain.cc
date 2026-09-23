#include <iostream>
#include <string>

#include <Common/test_log.h>

#include <Geometry_Tests/test_loops.h>
#include <Geometry_Tests/test_raycasting.h>

int main() {
	test_loops();
	test_raycasts();

	return EXIT_SUCCESS;
}