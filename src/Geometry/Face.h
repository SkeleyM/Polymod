#pragma once

#include <vector>

typedef struct TriangleIds {
	int v0;
	int v1;
	int v2;
} TriangleIds;

typedef struct Face {
	std::vector<int> vertices;

	Face(std::vector<int> vertices) {
		this->vertices = vertices;
	}

	std::vector<TriangleIds> triangulate();
} Face;