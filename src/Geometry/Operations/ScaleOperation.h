#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>

class ScaleOperation : public AbstractGeometryOperation {
public:
	Vector3 scale;

	ScaleOperation(Geometry geometry, SelectedGeometry selection, Vector3 scale)
		: AbstractGeometryOperation(geometry, selection) {
		this->scale = scale;
	}

	Geometry do_operation() override;

	void set_offset(Vector3 scale) {
		this->scale = scale;
	}
};