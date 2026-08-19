#pragma once

#include <string>

class AbstractOperationArgument {
public:
	std::string name;
	virtual void render() {
		abort();
	}
};