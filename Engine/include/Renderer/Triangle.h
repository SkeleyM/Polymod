#pragma once
#include <Renderer/Vertex.h>

typedef struct Triangle {
	Vertex vertices[3];

	Triangle(Vertex v0, Vertex v1, Vertex v2);
} Triangle;