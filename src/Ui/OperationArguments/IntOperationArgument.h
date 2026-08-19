#pragma once
#include <Ui/OperationArguments/AbstractOperationArgument.h>

class IntOperationArgument : public AbstractOperationArgument {
private:
	int* argument{ nullptr };
public:
	IntOperationArgument(std::string name, int* argument);

	void render() override;
};