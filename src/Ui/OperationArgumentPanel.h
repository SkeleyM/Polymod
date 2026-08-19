#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>
#include <Ui/OperationArguments/AbstractOperationArgument.h>

#include <vector>


class OperationArgumentPanel {
private:
	AbstractGeometryOperation* operation;
	std::vector<AbstractOperationArgument*> arguments;

	std::function<void(AbstractGeometryOperation*)> done_callback;
public:
	OperationArgumentPanel(AbstractGeometryOperation* operation, std::function<void(AbstractGeometryOperation*)> done_callback);

	void render();

	void add_argument(AbstractOperationArgument* argument);
	AbstractOperationArgument* get_argument(std::string name);
	AbstractGeometryOperation* get_operation();
};