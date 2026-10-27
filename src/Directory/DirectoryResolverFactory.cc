#include <DirectoryResolverFactory.h>

#include <MacResolver/MacResolver.h>
#include <LinuxResolver/LinuxResolver.h>
#include <WindowsResolver/WindowsResolver.h>

Polymodel::Directory::AbstractDirectoryResolver* Polymodel::Directory::create_os_resolver(std::string name) {
#ifdef _WIN32
	return new Polymodel::Directory::WindowsResolver(name);
#endif // __WIN32

#ifdef __linux__
	return new Polymodel::Directory::LinuxResolver(name);
#endif // __linux__

#ifdef __APPLE__
	return new Polymodel::Directory::MacResolver(name);
#endif // __APPLE__

	abort();
}