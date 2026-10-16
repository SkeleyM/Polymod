#pragma once

#include <ApplicationContext.h>

#include <PolymodProject/PolymodProject.h>
#include <Geometry/Formats/GeometryFormats.h>

#include <Ui/Primitives/PrimitiveOperationPanels.h>
#include <Ui/MenuBar/MenuBar.h>
#include <Ui/MenuBar/Menu.h>
#include <Ui/MenuBar/MenuBarItem.h>

#include <memory>

#include <nfd.h>

namespace Polymodel::Init {
	std::unique_ptr<MenuBar> CreateMenuBar() {
		std::unique_ptr<MenuBar> menubar = std::make_unique<MenuBar>();

		// Initialise menus
		Menu file_menu("File");
		Menu edit_menu("Edit");
		Menu add_menu("Add");


		MenuBarItem save_project("Save", []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto project_manager = app_context.get_project_manager();
			if (project_manager.expired() || !project_manager.lock().get()) return;

			nfdu8char_t* save_path;
			nfdu8char_t* default_path = "Documents/";
			NFD_PickFolder(&save_path, default_path);

			Polymodel::Project::export_project(save_path, project_manager);
			});

		// File menu items
		MenuBarItem import_obj("Import obj", []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto project_manager = app_context.get_project_manager();
			if (project_manager.expired() || !project_manager.lock().get()) return;

			// Save file dialogue boilerplate
			nfdu8char_t* in_path;
			nfdu8filteritem_t filters[2] = { { "Wavefront obj", "obj" } };
			nfdopendialogu8args_t args = { 0 };
			args.filterList = filters;
			args.filterCount = 1;
			auto result = NFD_OpenDialog_With(&in_path, &args);

			if (result == NFD_OKAY) {
				GeometryFormat::GeometryFormatSpec export_spec;
				export_spec.geometry_format = GeometryFormat::GeometryFormatType::WavefrontObj;
				GeometryFormat::GeometryFormatFactory format_factory;
				auto format = format_factory.create_format(export_spec);
				auto import_result = GeometryFormat::GeometryFileHandler::import_geometry(format.get(), std::string((char*)in_path));

				// If file imported successfully
				if (import_result.has_value()) {
					auto& manager = project_manager.lock().get()->get_geometry_manager();
					// the geometry will take on the name of the imported geometry.
					auto geometry = manager.create_new_geometry("ImportedPlaceholder");
					*geometry.lock() = import_result.value();
					geometry.lock().get()->name = "Imported";
				}
				NFD_FreePathU8(in_path);
			}
			else if (result == NFD_CANCEL) {
				// Cancelled
			}


			});

		MenuBarItem export_obj("Export as obj", []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto project_manager = app_context.get_project_manager();
			if (project_manager.expired() || !project_manager.lock().get()) return;

			auto& geometry_editor = app_context.get_geometry_editor();

			// Save file dialogue boilerplate
			nfdu8char_t* out_path;
			nfdu8filteritem_t filters[2] = { { "Wavefront obj", "obj" } };
			nfdsavedialogu8args_t args = { 0 };
			args.defaultName = "exported.obj";
			args.filterList = filters;
			args.filterCount = 1;
			auto result = NFD_SaveDialog_With(&out_path, &args);

			if (result == NFD_OKAY) {
				GeometryFormat::GeometryFormatSpec export_spec;
				export_spec.geometry_format = GeometryFormat::GeometryFormatType::WavefrontObj;
				GeometryFormat::GeometryFormatFactory format_factory;
				auto format = format_factory.create_format(export_spec);
				GeometryFormat::GeometryFileHandler::export_geometry(format.get(), *geometry_editor.get_current_geometry().lock().get(), std::string((char*)out_path));
				NFD_FreePathU8(out_path);
			}
			else if (result == NFD_CANCEL) {
				// Cancelled
			}
			});

		file_menu.add_menu_item(save_project);
		file_menu.add_menu_item(import_obj);
		file_menu.add_menu_item(export_obj);

		// Edit menu items
		MenuBarItem undo("Undo", []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			geometry_editor.undo();
			});
		MenuBarItem redo("Redo", []() {
			ApplicationContext& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();

			geometry_editor.redo();
			});
		edit_menu.add_menu_item(undo);
		edit_menu.add_menu_item(redo);

		// Add menu items
		MenuBarItem add_selector("Add Primitive", []() {
			auto& app_context = ApplicationContext::get_instance();
			auto& geometry_editor = app_context.get_geometry_editor();
			auto& toolbar = geometry_editor.get_toolbar();

			auto create_primitive_tool = new CreatePrimitiveTool(GeometryPrimitives::Cube);
			toolbar.simulate_tool_click(create_primitive_tool);
			});
		add_menu.add_menu_item(add_selector);

		// Add Menus to menubar
		menubar->add_menu(file_menu);
		menubar->add_menu(edit_menu);
		menubar->add_menu(add_menu);

		return menubar;
	}
}