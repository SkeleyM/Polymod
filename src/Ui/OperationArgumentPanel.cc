#include <Ui/OperationArgumentPanel.h>

#include <imgui.h>

OperationArgumentPanel::OperationArgumentPanel(
	AbstractGeometryOperation* operation,
	std::function<void(AbstractGeometryOperation*)> done_callback,
	std::function<void()> cancel_callback
) {
	this->operation = operation;
	this->done_callback = done_callback;
	this->cancel_callback = cancel_callback;
}

void OperationArgumentPanel::render() {
	ImGui::Begin("Operation");

	for (auto arg : this->arguments) {
		arg->render();
	}

	if (ImGui::Button("Done")) {
		this->done_callback(this->operation);
	}

	ImGui::SameLine();
	if (ImGui::Button("Cancel")) {
		this->cancel_callback();
	}

	ImGui::End();
}

void OperationArgumentPanel::add_argument(AbstractOperationArgument* argument) {
	this->arguments.push_back(argument);
}

AbstractOperationArgument* OperationArgumentPanel::get_argument(std::string name) {
	for (auto arg : this->arguments) {
		if (arg->name == name) {
			return arg;
		}
	}
	abort();
}

AbstractGeometryOperation* OperationArgumentPanel::get_operation() {
	return this->operation;
}