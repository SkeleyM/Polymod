#pragma once
#include <EMath.h>

typedef struct Vertex {
	Vector3 position;
	Vector3 normal;
	Vector3 colour;

	Vertex();
	Vertex(Vector3 position);
	Vertex(Vector3 position, Vector3 normal);
	Vertex(Vector3 position, Vector3 normal, Vector3 Colour);
} Vertex;