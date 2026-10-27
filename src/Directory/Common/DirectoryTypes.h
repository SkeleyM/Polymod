#pragma once

namespace Polymodel::Directory {
	enum class UserDirectoryType {
		HOME,
		DESKTOP,
		DOCUMENTS,
		DOWNLOADS,
		MUSIC,
		PICTURES,
		VIDEOS,
	};

	enum class ApplicationDirectoryType {
		GLOBAL,
		LOCAL,
	};
}