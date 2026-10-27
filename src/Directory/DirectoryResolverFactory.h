#include <Common/AbstractDirectoryResolver.h>

#include <string>

namespace Polymodel::Directory {
	AbstractDirectoryResolver* create_os_resolver(std::string name);
}