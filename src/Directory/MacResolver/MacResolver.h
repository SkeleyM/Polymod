#pragma once

#include <Common/AbstractDirectoryResolver.h>

namespace Polymodel::Directory {
	class MacResolver : public AbstractDirectoryResolver {
	public:
		MacResolver(std::string name) {
			this->name = name;
		}

		std::filesystem::path resolve_application_directory(ApplicationDirectoryType app_dir) {
			auto base_path = std::filesystem::path(std::getenv("HOME")) / "Library";

			switch (app_dir) {
			case(ApplicationDirectoryType::GLOBAL): {
				return base_path / "Application Support" / this->name;
			}
			case(ApplicationDirectoryType::LOCAL): {
				return base_path / "Containers" / this->name;
			}
			}
		}

		std::filesystem::path resolve_user_directory(UserDirectoryType user_dir) {
			auto base_path = std::filesystem::path(std::getenv("HOME"));
			switch (user_dir) {
			case(UserDirectoryType::DESKTOP): {
				return base_path / "Desktop";
			}
			case(UserDirectoryType::DOCUMENTS): {
				return base_path / "Documents";
			}
			case(UserDirectoryType::DOWNLOADS): {
				return base_path / "Downloads";
			}
			case(UserDirectoryType::HOME): {
				return base_path;
			}
			case(UserDirectoryType::MUSIC): {
				return base_path / "Music";
			}
			case(UserDirectoryType::PICTURES): {
				return base_path / "Pictures";
			}
			case(UserDirectoryType::VIDEOS): {
				return base_path / "Movies";
			}
			}
		}
	};
}