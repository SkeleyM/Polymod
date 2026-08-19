#pragma once

#include <Ui/ToolbarTool.h>

#include <vector>
#include <functional>

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
	void collapse();
	void expand();

	void add_tool(ToolbarTool* tool);
};