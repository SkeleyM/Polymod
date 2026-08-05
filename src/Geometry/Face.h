#pragma once

#include <vector>
#include <EMath.h>
#include <Geometry/GeometryShadingType.h>

typedef struct TriangleIds {
	int v0;
	int v1;
	int v2;
} TriangleIds;

typedef struct Face {
	std::vector<int> vertices;

	// Used for storing flat shading normals for the face. If the shading type is smooth, this will be ignored.
	GeometryShadingType shading_type{SHADE_FLAT};
	Vector3 face_normal;

	Face(std::vector<int> vertices) {
		this->vertices = vertices;
	}

	std::vector<TriangleIds> triangulate();
} Face;