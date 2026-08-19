#pragma once
#include <Ui/OperationArguments/AbstractOperationArgument.h>

class FloatOperationArgument : public AbstractOperationArgument {
private:
	float* argument{ nullptr };
public:
	FloatOperationArgument(std::string name, float* argument);

	void render() override;
};