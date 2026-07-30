#pragma once

#include <string>
#include <vector>

#include <EMath.h>
#include <Transform.h>
#include <Renderer/Mesh.h>
#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>

#include <Geometry/Face.h>

class Geometry {
private:
	std::vector<Vertex> vertices;
	std::vector<std::vector<int>> connections;
	std::vector<Face> faces;
public:
	std::string name;

	Transform transform;

	void add_vertex(Vector3 vertex);
	void add_connection(int v1, int v2);
	void define_face(std::vector<int> vertices);
	std::vector<int> get_neighbours(int vertex);
	Geometry copy();
	Mesh triangulate();
};