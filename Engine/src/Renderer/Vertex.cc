#include <Renderer/Vertex.h>

// Required a default constructor to be passed as an argument
Vertex::Vertex() {
	this->position = Vector3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(Vector3 position) {
	this->position = position;
	this->normal = Vector3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(Vector3 position, Vector3 normal) {
	this->position = position;
	this->normal = normal;
}
