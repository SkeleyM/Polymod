#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>

class ScaleOperation : public AbstractGeometryOperation {
private:
	Vector3 scale;
public:

	ScaleOperation(Geometry geometry, SelectedGeometry selection, Vector3 scale)
		: AbstractGeometryOperation(geometry, selection) {
		this->scale = scale;
	}

	Geometry do_operation() override;

	void set_offset(Vector3 scale) {
		this->scale = scale;
	}
};