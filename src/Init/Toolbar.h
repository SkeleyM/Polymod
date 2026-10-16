#pragma once

namespace Polymodel::Init::GeometryEditor {
	void initialise_toolbar(Toolbar& toolbar) {
		toolbar.add_tool(new MoveTool());
		toolbar.add_tool(new ScaleTool());
		toolbar.add_tool(new RotateTool());
		toolbar.add_tool(new ExtrudeTool());
		toolbar.add_tool(new VertexSpinTool());
	}
}