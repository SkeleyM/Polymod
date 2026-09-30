#pragma once

#include <Ui/Primitives/PrimitiveSelector.h>

class CreateNewGeometryPanel {
private:
	PrimitiveSelector primitiveSelector;

	std::string new_geometry_name_buffer;
	bool name_set{ false };
public:
	CreateNewGeometryPanel();
	~CreateNewGeometryPanel();

	bool completed{ false };

	std::string get_name() {
		return this->new_geometry_name_buffer;
	}

	GeometryPrimitives::GeometryPrimitive get_primitive();
	void render();
};