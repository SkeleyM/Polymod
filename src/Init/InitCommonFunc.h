#pragma once

#include <ApplicationContext.h>
#include <PolymodProject/PolymodProject.h>

#include <string>
#include <optional>

namespace Polymodel::Init::CommonFuncs {
	void save_active_project() {
		ApplicationContext& app_context = ApplicationContext::get_instance();
		auto project_manager = app_context.get_project_manager();
		if (project_manager.expired() || !project_manager.lock().get()) return;

		Polymodel::Project::export_project(project_manager);
	}
}