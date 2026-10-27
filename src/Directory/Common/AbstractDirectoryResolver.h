#pragma once

#include <Common/DirectoryTypes.h>

#include <string>
#include <filesystem>

namespace Polymodel::Directory {
	class AbstractDirectoryResolver {
	public:
		std::string name;
		virtual std::filesystem::path resolve_application_directory(ApplicationDirectoryType app_dir) = 0;
		virtual std::filesystem::path resolve_user_directory(UserDirectoryType user_dir) = 0;
	};
}