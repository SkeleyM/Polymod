#pragma once

#include <PolymodProject/ProjectManager.h>
#include <GeometryEditor.h>
#include <EditorUI.h>
#include <ShortcutManager.h>

#include <memory.h>

class EditorUI;

class ApplicationContext {
	static ApplicationContext* instance;

private:
	std::shared_ptr<PolymodProject::ProjectManager> project_manager;
	GeometryEditor geometry_editor = GeometryEditor();
public:
	ShortcutManager shortcut_manager = ShortcutManager();
	EditorUI* editor_ui;
public:
	static ApplicationContext& get_instance();

	std::weak_ptr<PolymodProject::ProjectManager> get_project_manager();
	void set_project_manager(std::shared_ptr<PolymodProject::ProjectManager> project_manager);
	GeometryEditor& get_geometry_editor();
};