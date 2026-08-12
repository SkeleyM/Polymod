#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>

class ExtrudeOperation : public AbstractGeometryOperation {
private:
	Vector3 extrusion;
public:
	ExtrudeOperation(Geometry input_geometry, SelectedGeometry selection, Vector3 extrusion) 
		: AbstractGeometryOperation(input_geometry, selection) {
		this->extrusion = extrusion;
	}

	Geometry do_operation() override;

	void set_extrusion(Vector3 extrusion) {
		this->extrusion = extrusion;
	}
};