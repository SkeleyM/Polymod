#include <AxisGrid.h>

void AxisGrid::set_axis_flag(AxisFlags flag) {
	this->render_axis = static_cast<AxisFlags>(this->render_axis | flag);
}

void AxisGrid::clear_axis_flag(AxisFlags flag) {
	this->render_axis = static_cast<AxisFlags>(this->render_axis & !flag);
}

void AxisGrid::set_grid_density(float grid_density) {
	this->grid_density = grid_density;
}

void AxisGrid::set_grid_radius(int grid_radius) {
	this->grid_radius = grid_radius;
}

void AxisGrid::render(Camera& camera) {
	// Render the axis;
	if (this->render_axis & X) {
		this->axis_renderer.render_line(camera, Line{
			Vector3(-this->grid_radius, 0.0f, 0.0f),
			Vector3(this->grid_radius, 0.0f, 0.0f),
			Vector3(1.0f, 0.0f, 0.0f)
		});
	}
	if (this->render_axis & Y) {
		this->axis_renderer.render_line(camera, Line{
			Vector3(0.0f, -this->grid_radius, 0.0f),
			Vector3(0.0f, this->grid_radius, 0.0f),
			Vector3(0.0f, 1.0f, 0.0f)
		});
	}
	if (this->render_axis & Z) {
		this->axis_renderer.render_line(camera, Line {
			Vector3(0.0f, 0.0f, -this->grid_radius),
			Vector3(0.0f, 0.0f, this->grid_radius),
			Vector3(0.0f, 0.0f, 1.0f)
		});
	}

	// Render the grid
	std::vector<Line> lines;
	for (float grid = -this->grid_radius; grid <= this->grid_radius; grid += this->grid_density) {
		lines.push_back(Line{
			Vector3(grid, 0.0f, -this->grid_radius),
			Vector3(grid, 0.0f, this->grid_radius),
			Vector3(0.3f, 0.3f, 0.3f)
		});
		lines.push_back(Line{
			Vector3(-this->grid_radius, 0.0f, grid),
			Vector3(this->grid_radius, 0.0f, grid),
			Vector3(0.3f, 0.3f, 0.3f)
		});
	}

	this->axis_renderer.render_lines(camera, lines);
}