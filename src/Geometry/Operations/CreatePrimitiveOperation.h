#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>
#include <Geometry/GeometryPrimitives.h>

class CreatePrimitiveOperation : public AbstractGeometryOperation {
public:
	GeometryPrimitives::GeometryPrimitive primitive_type{ GeometryPrimitives::Cube };
	Vector3 position{ 0.0f };
	float diameter{ 1.0f };

	int iterations{ 16 };
	int segments{ 16 };
	float height{ 1.0f };
	float hole { 1.0f };

	CreatePrimitiveOperation(Geometry input_geometry, SelectedGeometry selection, GeometryPrimitives::GeometryPrimitive primitive_type, Vector3 position, float diameter)
		: AbstractGeometryOperation(input_geometry, selection) {
		this->primitive_type = primitive_type;
		this->position = position;
		this->diameter = diameter;
	}

	Geometry do_operation() override;
};