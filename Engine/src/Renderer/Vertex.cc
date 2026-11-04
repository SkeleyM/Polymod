#include <Renderer/Vertex.h>

// Required a default constructor to be passed as an argument
Vertex::Vertex() {}

Vertex::Vertex(Vector3 position) {
	this->position = position;
}

Vertex::Vertex(Vector3 position, Vector3 normal) {
	this->position = position;
	this->normal = normal;
}

Vertex::Vertex(Vector3 position, Vector3 normal, Vector3 colour) {
	this->position = position;
	this->normal = normal;
	this->colour = colour;
}

Vertex::Vertex(Vector3 position, Vector3 normal, Vector3 Colour, Vector2 texture) {
	this->position = position;
	this->normal = normal;
	this->colour = colour;
	this->texture = texture;
}