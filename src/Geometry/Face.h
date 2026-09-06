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
	Vector3 face_colour;

	Face(std::vector<int> vertices) {
		this->vertices = vertices;
		this->face_colour = { 0.4f, 0.4f, 0.4f };
	}

	std::vector<TriangleIds> triangulate();

	bool operator ==(const Face & other) const {
		if (this->vertices.size() != other.vertices.size()) {
			return false;
		}
		for (int i = 0; i < this->vertices.size(); i++) {
			if (this->vertices[i] != other.vertices[i]) {
				return false;
			}
		}
		return true;
	}
} Face;