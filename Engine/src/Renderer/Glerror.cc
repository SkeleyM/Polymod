#include <Renderer/Glerror.h>

void gl_check_for_error() {
#ifndef NDEBUG
	auto error = glGetError();
	while (error) {
		std::cout << "Gl Error;" << " Code: " << error << std::endl;
		error = glGetError();
	}
#endif
}