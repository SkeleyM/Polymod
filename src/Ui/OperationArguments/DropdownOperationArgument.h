#pragma once
#include <Ui/OperationArguments/AbstractOperationArgument.h>

#include <vector>

#include <imgui.h> 
#include <assert.h>


template <typename T>
class DropdownOperationArgument : public AbstractOperationArgument {
private:
	T* argument{ nullptr };

	using Combo = std::pair<std::string, T>;
	std::vector<Combo> options;
	size_t selected_index{ 0 };
public:


	DropdownOperationArgument(std::string name, T* argument, std::vector<Combo> options);

	void render() override;
};

template<typename T>
DropdownOperationArgument<T>::DropdownOperationArgument(std::string name, T* argument, std::vector<Combo> options) {
	this->name = name;
	this->argument = argument;
	this->options = options;
}

template<typename T>
void DropdownOperationArgument<T>::render() {
	assert(this->argument != nullptr);

	if (ImGui::BeginCombo(this->name.c_str(), this->options[this->selected_index].first.c_str())) {
		for (int o = 0; o < this->options.size(); o++) {
			auto option = this->options[o];
			if (ImGui::Selectable(option.first.c_str())) {
				*this->argument = option.second;
				this->selected_index = o;
			}
		}
		ImGui::EndCombo();
	}
}