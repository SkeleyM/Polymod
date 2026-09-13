#pragma once

#include <AxisFlags.h>
#include <Renderer/LineRenderer.h>

class AxisGrid {
private:
	LineRenderer axis_renderer;
	AxisFlags render_axis { static_cast<AxisFlags>(X | Z) };
	int grid_radius { 10 };
	float grid_density { 0.5f };
public:
	void set_axis_flag(AxisFlags flag);
	void clear_axis_flag(AxisFlags flag);
	void set_grid_density(float grid_density);
	void set_grid_radius(int grid_radius);

	void render(Camera& camera);
};