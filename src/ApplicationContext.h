#pragma once

#include <PolymodProject/ProjectManager.h>
#include <PolymodProject/RecentProjects.h>
#include <Directory/DirectoryResolver.h>
#include <ReferenceImages/ReferenceImageManager.h>
#include <GeometryEditor.h>
#include <EditorUI.h>
#include <ShortcutManager.h>

#include <memory.h>

class EditorUI;

class ApplicationContext {
	static ApplicationContext* instance;

private:
	std::shared_ptr<Polymodel::Project::ProjectManager> project_manager;
	GeometryEditor geometry_editor = GeometryEditor();
	ReferenceImageManager reference_image_manager = ReferenceImageManager();
public:
	ShortcutManager shortcut_manager = ShortcutManager();
	RecentProjects recent_projects;
	Polymodel::Directory::AbstractDirectoryResolver* directory_resolver;
	EditorUI* editor_ui;
public:
	static ApplicationContext& get_instance();
	static void on_exit();

	std::weak_ptr<Polymodel::Project::ProjectManager> get_project_manager();
	void set_project_manager(std::shared_ptr<Polymodel::Project::ProjectManager> project_manager);
	ReferenceImageManager& get_reference_image_manager();
	GeometryEditor& get_geometry_editor();
};