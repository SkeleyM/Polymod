#pragma once

#include <string>
#include <vector>
#include <optional>
#include <set>
#include <stack>

#include <EMath.h>
#include <Transform.h>
#include <Renderer/Mesh.h>
#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>

#include <Geometry/Face.h>
#include <Geometry/GeometryShadingType.h>

class Geometry {
private:
	std::vector<Vertex> vertices;
	std::vector<std::vector<int>> connections;
	std::vector<Face> faces;

	void calculate_face_normals(int face_index, GeometryShadingType shading_type);
public:
	Geometry() {}
	Geometry(std::string name);

	std::string name;

	Transform transform;

	int add_vertex(Vector3 vertex);
	Vertex& get_vertex(int v_id);
	std::vector<int> get_all_vertex_ids();
	std::vector<Face>& get_faces();
	void add_connection(int v1, int v2);
	void define_face(std::vector<int> vertices);
	std::vector<int> get_neighbours(int vertex);
	std::optional<std::vector<int>> get_loop(std::vector<int> vertices);
	bool are_vertices_connected(int v1, int v2);
	void calculate_normals(GeometryShadingType shading_type);
	Geometry copy();
	Mesh triangulate();
};