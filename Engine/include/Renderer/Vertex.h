#pragma once
#include <EMath.h>

typedef struct Vertex {
	Vector3 position{ 0.0f, 0.0f, 0.0f };
	Vector3 normal{ 0.3f, 0.3f, 0.3f };
	Vector3 colour{ 1.0f, 1.0f, 1.0f };
	Vector2 texture{ 0.0f, 0.0f };

	Vertex();
	Vertex(Vector3 position);
	Vertex(Vector3 position, Vector3 normal);
	Vertex(Vector3 position, Vector3 normal, Vector3 Colour);
	Vertex(Vector3 position, Vector3 normal, Vector3 Colour, Vector2 texture);
} Vertex;