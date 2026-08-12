#include <Geometry/Timeline.h>

Timeline::Timeline() {}

void Timeline::push_operation(std::shared_ptr<AbstractGeometryOperation> operation) {
	this->operations.push_back(operation);
}

std::weak_ptr<AbstractGeometryOperation> Timeline::peek_operation(int offset) {
	return this->operations[this->operations.size() - offset - 1];
}

std::shared_ptr<AbstractGeometryOperation> Timeline::pop_operation() {
	std::shared_ptr<AbstractGeometryOperation> op = std::move(*this->operations.rbegin());
	this->operations.pop_back();
	return op;
}

std::vector<std::weak_ptr<AbstractGeometryOperation>> Timeline::get_operations() {
	std::vector<std::weak_ptr<AbstractGeometryOperation>> operation_references;
	operation_references.reserve(this->operations.size());
	for (int i = 0; i < this->operations.size(); i++) {
		operation_references.push_back(
			this->operations[i]
		);
	}
	return operation_references;
}
