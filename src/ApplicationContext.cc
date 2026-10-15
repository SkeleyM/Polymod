#include <ApplicationContext.h>


ApplicationContext* ApplicationContext::instance = nullptr;

ApplicationContext& ApplicationContext::get_instance() {
	if (!instance) {
		instance = new ApplicationContext();
		instance->editor_ui = new EditorUI();
	}
	return *instance;
}

std::weak_ptr<PolymodProject::ProjectManager> ApplicationContext::get_project_manager() {
	return this->project_manager;
}

void ApplicationContext::set_project_manager(std::shared_ptr<PolymodProject::ProjectManager> project_manager) {
	this->project_manager = project_manager;
}

GeometryEditor& ApplicationContext::get_geometry_editor() {
	return this->geometry_editor;
}