#pragma once
#include <optional>
#include <vector>

#include <Geometry/Geometry.h>
#include <Geometry/Face.h>

typedef struct SelectedGeometry {
	std::optional<std::vector<int>> selected_vertices;
	std::optional<std::vector<std::pair<int, int>>> selected_edges;
	std::optional<std::vector<Face>> selected_faces;
} SelectedGeometry;

class AbstractGeometryOperation {
public:
	AbstractGeometryOperation(Geometry input_geometry, SelectedGeometry selection) {
		this->input_geometry = input_geometry;
		this->selection = selection;
	}

	Geometry input_geometry;
	SelectedGeometry selection;

	std::optional<std::vector<int>> affected_vertices;
	std::optional<std::vector<std::pair<int, int>>> affected_edges;

	virtual Geometry do_operation() {
		return Geometry();
	}

	// This will convert any input geometry to a large list of vertex id's
	// This will also remove any order, this means if the operation requires order then do not use this.
	std::vector<int> selection_as_vertices();
};