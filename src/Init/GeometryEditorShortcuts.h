#pragma once 

#include <ApplicationContext.h>

#include <GeometryEditor.h>
#include <ShortcutManager.h>

#include <Ui/ToolbarTool/MoveTool.h>
#include <Ui/ToolbarTool/RotateTool.h>
#include <Ui/ToolbarTool/ScaleTool.h>
#include <Ui/ToolbarTool/ExtrudeTool.h>
#include <Ui/ToolbarTool/VertexSpinTool.h>

namespace Polymodel::Init::Shortcuts {
	void register_geometry_editor_shortcuts(ShortcutManager& shortcut_manager) {
		// Add shortcuts
		shortcut_manager.add_shortcut({ GLFW_KEY_Z, MODIFIER_CONTROL, []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			geometry_editor.undo();
		}, true });

		shortcut_manager.add_shortcut({ GLFW_KEY_Z, MODIFIER_CONTROL | MODIFIER_SHIFT, []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			geometry_editor.redo();
		}, true });

		shortcut_manager.add_shortcut({ GLFW_KEY_ESCAPE, MODIFIER_NONE, []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			if (geometry_editor.is_performing_operation())
				geometry_editor.cancel_operation();
			else {
				geometry_editor.set_selection({});
			}
		}, true });

		// Tool shortcuts
		shortcut_manager.add_shortcut({ GLFW_KEY_E, MODIFIER_NONE, []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			Toolbar& toolbar = geometry_editor.get_toolbar();
			toolbar.simulate_tool_click(new ExtrudeTool());
		}, true });

		shortcut_manager.add_shortcut({ GLFW_KEY_S, MODIFIER_NONE, []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			Toolbar& toolbar = geometry_editor.get_toolbar();
			toolbar.simulate_tool_click(new ScaleTool());
		}, true });

		shortcut_manager.add_shortcut({ GLFW_KEY_R, MODIFIER_NONE, []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			Toolbar& toolbar = geometry_editor.get_toolbar();
			toolbar.simulate_tool_click(new RotateTool());
		}, true });

		shortcut_manager.add_shortcut({ GLFW_KEY_M, MODIFIER_NONE, []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			Toolbar& toolbar = geometry_editor.get_toolbar();
			toolbar.simulate_tool_click(new MoveTool());
		}, true });
	}
}