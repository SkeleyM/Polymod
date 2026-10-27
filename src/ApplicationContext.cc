#include <ApplicationContext.h>
#include <Engine.h>

#include <fstream>
#include <sstream>

ApplicationContext* ApplicationContext::instance = nullptr;

ApplicationContext& ApplicationContext::get_instance() {
	if (!instance) {
		instance = new ApplicationContext();
		instance->editor_ui = new EditorUI();
		instance->directory_resolver = Polymodel::Directory::create_os_resolver("Polymodel");

		// Get recent project if they exist
		auto app_data_path = instance->directory_resolver->resolve_application_directory(Polymodel::Directory::ApplicationDirectoryType::LOCAL);
		auto recent_projects_file = app_data_path / "recent_projects.json";
		if (std::filesystem::exists(recent_projects_file)) {
			auto file = std::ifstream(recent_projects_file, std::ios::in);
			std::stringstream file_data;
			file_data << file.rdbuf();

			auto deserialised_projects = RecentProjects::deserialize(file_data.str());
			if (deserialised_projects.has_value()) {
				instance->recent_projects = deserialised_projects.value();
			}
		}
		
	}
	return *instance;
}

void ApplicationContext::on_exit() {
	auto& app_context = ApplicationContext::get_instance();

	auto app_data_path = instance->directory_resolver->resolve_application_directory(Polymodel::Directory::ApplicationDirectoryType::LOCAL);
	// Ensure appdata folder structure exists
	std::filesystem::create_directories(app_data_path);

	// On app destroy save the recent projects
	auto recent_projects_file_path = app_data_path / "recent_projects.json";
	auto recent_projects_file = std::ofstream(recent_projects_file_path, std::ios::out);
	// Override file
	recent_projects_file.clear();
	recent_projects_file << app_context.recent_projects.serialize();
	recent_projects_file.close();
}

std::weak_ptr<Polymodel::Project::ProjectManager> ApplicationContext::get_project_manager() {
	return this->project_manager;
}

void ApplicationContext::set_project_manager(std::shared_ptr<Polymodel::Project::ProjectManager> project_manager) {
	this->project_manager = project_manager;
	this->recent_projects.push_project(project_manager->get_project_path());

	// Make sure to clear all meshes if the current project was just discarded
	if (this->project_manager == nullptr) {
		Engine* engine = Engine::get_instance();
		engine->get_active_scene().clear_scene();
	}
}

GeometryEditor& ApplicationContext::get_geometry_editor() {
	return this->geometry_editor;
}