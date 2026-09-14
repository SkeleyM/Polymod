#pragma once
#include <Ui/OperationArguments/AbstractOperationArgument.h>

class FloatOperationArgument : public AbstractOperationArgument {
private:
	float increment{ 0.1f };
	float* argument{ nullptr };
public:
	FloatOperationArgument(std::string name, float* argument, float increment = 0.1f);

	void render() override;
};