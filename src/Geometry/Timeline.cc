#include <Geometry/Timeline.h>

Timeline::Timeline() {}

void Timeline::push_operation(std::shared_ptr<AbstractGeometryOperation> operation) {
	// If we are pushing a new operation after rewinding, we need to discard all operations after the current index
	if (this->current_operation_index < this->operations.size() - 1) {
		this->operations.erase(this->operations.begin() + this->current_operation_index + 1, this->operations.end());
	}

	this->operations.push_back(operation);
	this->forward();
}

std::weak_ptr<AbstractGeometryOperation> Timeline::peek_operation(int offset) {
	return this->operations[this->current_operation_index - offset];
}

std::shared_ptr<AbstractGeometryOperation> Timeline::pop_operation() {
	if (this->operations.size() == 0) return nullptr;
	std::shared_ptr<AbstractGeometryOperation> op = this->operations[this->current_operation_index];
	this->rewind();
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

Geometry Timeline::reconstruct_from_point(int offset_from_present) {
	if (offset_from_present == 0) {
		return this->get_present_geometry();
	}

	int base = this->operations.size() - offset_from_present;
	Geometry geometry;
	for (int i = base; i < this->operations.size(); i++) {
		auto curr_op = this->operations[i].get();
		geometry = curr_op->do_operation();

		if (i != this->operations.size()) {
			auto next_op = this->operations[i + 1].get();
			next_op->input_geometry = geometry;
			next_op->selection.selected_vertices = curr_op->affected_vertices;
			next_op->selection.selected_edges = curr_op->affected_edges;
		}
	}
	return geometry;
}

Geometry Timeline::get_present_geometry() {
	auto newest_operation = this->peek_operation();
	Geometry present_geometry = newest_operation.lock().get()->do_operation();
	return present_geometry;
}

void Timeline::rewind(int from_current) {
	this->current_operation_index -= from_current;
	if (this->current_operation_index < 0) 
		this->current_operation_index = 0;
}

void Timeline::forward(int from_current) {
	this->current_operation_index += from_current;
	if (this->current_operation_index >= this->operations.size())
		this->current_operation_index = this->operations.size();
}

void Timeline::to_present() {
	this->current_operation_index = this->operations.size();
}