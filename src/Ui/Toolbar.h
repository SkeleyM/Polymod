#pragma once

#include <EMath.h>

#include <Ui/ToolbarTool.h>

#include <vector>
#include <functional>

const Vector2 TOOLBAR_SIZE = {70.0f, 600.0f};

class Toolbar {
private:
	bool collapsed{ false };
	std::vector<ToolbarTool*> tools;

	std::function<void(ToolbarTool*)> on_tool_click;

	// Either will render the collapse button next to the toolbar or just the button to re collapsed
	void render_collapse();
public:
	Toolbar(std::function<void(ToolbarTool*)>);

	void render();
	void render_tooltip(ToolbarTool* tool);
	void collapse();
	void expand();

	void add_tool(ToolbarTool* tool);
};