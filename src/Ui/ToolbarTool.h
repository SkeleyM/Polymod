#pragma once

#include <Ui/OperationArgumentPanel.h>

#include <string>
#include <functional>

class GeometryEditor;
class ToolbarTool {
public:
	virtual OperationArgumentPanel create_panel(GeometryEditor* editor, std::function<void(AbstractGeometryOperation*)> done_callback) = 0;
	virtual std::string get_name() = 0;
};