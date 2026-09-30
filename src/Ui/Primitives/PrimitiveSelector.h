#pragma once

#include <Geometry/GeometryPrimitives.h>
#include <GeometryEditor.h>

class PrimitiveSelector {
private:
	Vector2 screen_position;
	GeometryPrimitives::GeometryPrimitive primitive;
	bool is_selection_ready{ false };
public:
	PrimitiveSelector(Vector2 screen_position);
	PrimitiveSelector();

	void set_screen_position(Vector2 screen_position);
	
	bool selection_ready();
	GeometryPrimitives::GeometryPrimitive get_primitive();
	void render();
};