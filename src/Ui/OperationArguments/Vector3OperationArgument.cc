#include <Ui/OperationArguments/Vector3OperationArgument.h>

#include <imgui.h>
#include <assert.h>

Vector3OperationArgument::Vector3OperationArgument(std::string name, Vector3* argument) {
	this->name = name;
	this->argument = argument;
}

void Vector3OperationArgument::render() {
	assert(this->argument != nullptr);

	ImGui::DragFloat3(this->name.c_str(), (float*)this->argument, 0.1f);
}