#pragma once

#include <Geometry/Operations/AbstractGeometryOperation.h>

#include <stack>
#include <vector>
#include <memory>

class Timeline {
	std::vector<std::shared_ptr<AbstractGeometryOperation>> operations;

public:
	Timeline();

	void push_operation(std::shared_ptr<AbstractGeometryOperation> operation);
	std::weak_ptr<AbstractGeometryOperation> peek_operation(int offset = 0);
	std::shared_ptr<AbstractGeometryOperation> pop_operation();
	// Returns a vector of pointers to the operations
	std::vector<std::weak_ptr<AbstractGeometryOperation>> get_operations();
	Geometry reconstruct_from_point(int offset_from_present);
	Geometry get_present_geometry();
};