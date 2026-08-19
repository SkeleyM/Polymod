#pragma once
#include <Ui/OperationArguments/AbstractOperationArgument.h>
#include <EMath.h>

class Vector3OperationArgument : public AbstractOperationArgument {
private:
	Vector3* argument{ nullptr };
public:
	Vector3OperationArgument(std::string name, Vector3* argument);

	void render() override;
};