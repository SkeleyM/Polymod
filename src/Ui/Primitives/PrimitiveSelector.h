#pragma once

#include <Geometry/GeometryPrimitives.h>
#include <GeometryEditor.h>

class PrimitiveSelector {
private:
	GeometryEditor* editor;
	Vector2 screen_position;
public:
	PrimitiveSelector(GeometryEditor* editor, Vector2 screen_position);

	void set_screen_position(Vector2 screen_position);

	void render();
};