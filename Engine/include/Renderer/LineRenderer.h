#pragma once

#include <vector>
#include <EMath.h>

struct Line {
	Vector3 start;
	Vector3 end;
	Vector3 colour;
};

class LineRenderer {
private:
	float line_width = 1.0f;
public:
	void set_line_width(float width);
	void render_lines(std::vector<Line>& lines);
	void render_line(Line& line);
};