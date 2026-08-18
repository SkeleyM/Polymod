#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>

class VertexSpinOperation : public AbstractGeometryOperation {
public:
	float angle_x;
	float angle_y;
	int samples;
	Vector3 origin;

	VertexSpinOperation(Geometry input_geometry, SelectedGeometry selection, Vector3 origin, int samples, float angle_x, float angle_y)
		: AbstractGeometryOperation(input_geometry, selection) {
		this->origin = origin;
		this->samples = samples;
		this->angle_x = angle_x;
		this->angle_y = angle_y;
	}

	Geometry do_operation() override;

	void set_origin(Vector3 origin) {
		this->origin = origin;
	}

	void set_angle_x(float angle_x) {
		this->angle_x = angle_x;
	}

	void set_angle_y(float angle_y) {
		this->angle_y = angle_y;
	}

	void set_samples(int samples) {
		this->samples = samples;
	}
};