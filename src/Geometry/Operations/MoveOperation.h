#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>

class MoveOperation : public AbstractGeometryOperation {
private:
	Vector3 offset;
public:
	MoveOperation(Geometry input_geometry, SelectedGeometry selection, Vector3 offset)
		: AbstractGeometryOperation(input_geometry, selection) {
		this->offset = offset;
	}

	Geometry do_operation() override;

	void set_offset(Vector3 offset) {
		this->offset = offset;
	}
};