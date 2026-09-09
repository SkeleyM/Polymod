#include <Ui/OperationArguments/FloatOperationArgument.h>

#include <imgui.h>
#include <assert.h>

FloatOperationArgument::FloatOperationArgument(std::string name, float* argument) {
	this->name = name;
	this->argument = argument;
}

void FloatOperationArgument::render() {
	assert(this->argument != nullptr);

	ImGui::DragFloat(this->name.c_str(), this->argument, 0.1f);
}