#include <Ui/OperationArgumentPanel.h>

#include <imgui.h>

OperationArgumentPanel::OperationArgumentPanel(AbstractGeometryOperation* operation, std::function<void(AbstractGeometryOperation*)> done_callback) {
	this->operation = operation;
	this->done_callback = done_callback;
}

void OperationArgumentPanel::render() {
	ImGui::Begin("Operation");

	for (auto arg : this->arguments) {
		arg->render();
	}

	if (ImGui::Button("Done")) {
		this->done_callback(this->operation);
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