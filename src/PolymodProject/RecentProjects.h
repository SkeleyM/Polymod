#pragma once

#include <nlohmann/json.hpp>

#include <filesystem>
#include <set>
#include <optional>

#define MAX_RECENT_PROJECTS 5

namespace Polymodel::Project {
	class RecentProjects {
	private:
		std::set<std::filesystem::path> recent_projects;
	public:
		RecentProjects() { }

		void push_project(std::filesystem::path project_path) {
			this->recent_projects.insert(project_path);
		}

		std::set<std::filesystem::path>& get_recent_project_paths() {
			return this->recent_projects;
		}

		std::string serialize() {
			nlohmann::json projects = {};
			auto size = recent_projects.size() > MAX_RECENT_PROJECTS ? MAX_RECENT_PROJECTS : recent_projects.size();
			for (int i = 0; i < size; i++) {
				projects[i] = this->recent_projects;
			}

			// Dont return json if empty, itll fail
			if (projects.empty()) return "";

			nlohmann::json json = {};
			json["previous"] = projects;

			auto serialized = json.dump();
			return serialized;
		}

		static std::optional<RecentProjects> deserialize(std::string json) {
			RecentProjects recent;

			try {
				auto parsed = nlohmann::json::parse(json);
				auto j = parsed["previous"];

				for (auto elem : j[0]) {
					// Ensure path is still valid
					if (std::filesystem::exists(elem)) {
						recent.recent_projects.insert(elem);
					}
				}
			}
			catch (std::exception e) {
				// Return what was parsed if it was partially parsed
				if (!recent.recent_projects.empty()) 
					return recent;
				return std::nullopt;
			}

			return recent;
		}
	};
}