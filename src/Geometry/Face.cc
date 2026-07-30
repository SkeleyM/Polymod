#include <Geometry/Face.h>

std::vector<TriangleIds> Face::triangulate() {
	std::vector<TriangleIds> triangles = std::vector<TriangleIds>();
	if (this->vertices.size() < 3)
		return triangles;

	for (int vert_id = 1; vert_id < this->vertices.size() - 1; vert_id++) {
		int constant_vert_id = this->vertices[0];
		int v2 = this->vertices[vert_id];
		int v3 = this->vertices[vert_id + 1];
		triangles.push_back({constant_vert_id, v2, v3});
	}

	return triangles;
}