#include <Renderer/Vertex.h>

// Required a default constructor to be passed as an argument
Vertex::Vertex() {
	this->position = Vector3(0.0f, 0.0f, 0.0f);
	this->normal = Vector3(0.0f, 0.0f, 0.0f);
	this->colour = Vector3(1.0f, 1.0f, 1.0f);
}

Vertex::Vertex(Vector3 position) {
	this->position = position;
	this->normal = Vector3(0.0f, 0.0f, 0.0f);
	this->colour = { 1.0f, 1.0f, 1.0f };
}

Vertex::Vertex(Vector3 position, Vector3 normal) {
	this->position = position;
	this->normal = normal;
	this->colour = { 1.0f, 1.0f, 1.0f };
}

Vertex::Vertex(Vector3 position, Vector3 normal, Vector3 colour) {
	this->position = position;
	this->normal = normal;
	this->colour = colour;
}
