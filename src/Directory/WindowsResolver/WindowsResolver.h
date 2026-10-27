#pragma once

#include <Common/AbstractDirectoryResolver.h>

namespace Polymodel::Directory {
	class WindowsResolver : public AbstractDirectoryResolver {
	public:
		WindowsResolver(std::string name) {
			this->name = name;
		}

		std::filesystem::path resolve_application_directory(ApplicationDirectoryType app_dir) {
			switch (app_dir) {
			case(ApplicationDirectoryType::GLOBAL): {
				auto appdata = std::string(std::getenv("appdata"));
				auto path = std::filesystem::path(appdata);
				return path / this->name;
			}
			case(ApplicationDirectoryType::LOCAL): {
				auto localappdata = std::string(std::getenv("localappdata"));
				auto path = std::filesystem::path(localappdata);
				return path / this->name;
			}
			default: {
				abort();
			}
			}
		}

		std::filesystem::path resolve_user_directory(UserDirectoryType user_dir) {
			auto user_profile_path = std::filesystem::path(std::getenv("userprofile"));
			switch (user_dir) {
			case(UserDirectoryType::DESKTOP): {
				return user_profile_path / "Desktop";
			}
			case(UserDirectoryType::DOCUMENTS): {
				return user_profile_path / "Documents";
			}
			case(UserDirectoryType::DOWNLOADS): {
				return user_profile_path / "Downloads";
			}
			case(UserDirectoryType::HOME): {
				return user_profile_path;
			}
			case(UserDirectoryType::MUSIC): {
				return user_profile_path / "Music";
			}
			case(UserDirectoryType::PICTURES): {
				return user_profile_path / "Pictures";
			}
			case(UserDirectoryType::VIDEOS): {
				return user_profile_path / "Videos";
			}
			default: {
				abort();
			}
			}
		}
	};
}