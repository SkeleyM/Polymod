#pragma once
#include <Geometry/Operations/AbstractGeometryOperation.h>

class RotateOperation : public AbstractGeometryOperation {
public:
	Vector3 axis;
	float angle;

	RotateOperation(Geometry input, SelectedGeometry selection, Vector3 axis, float angle) : AbstractGeometryOperation(input, selection) {
		this->axis = axis;
		this->angle = angle;
	}

	Geometry do_operation() override;

	void set_axis(Vector3 axis) {
		this->axis = axis;
	}

	void set_angle(float angle) {
		this->angle = angle;
	}
};