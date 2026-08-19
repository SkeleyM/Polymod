#include <Ui/OperationArguments/IntOperationArgument.h>

#include <imgui.h>
#include <assert.h>

IntOperationArgument::IntOperationArgument(std::string name, int* argument) {
	this->name = name;
	this->argument = argument;
}

void IntOperationArgument::render() {
	assert(this->argument != nullptr);

	ImGui::DragInt(this->name.c_str(), this->argument);
}