#include <Ui/GeometryEditor/SideWindow.h>
#include <GeometryManager.h>

#include <Engine.h>

void SideWindow::render(GeometryManager& geometry_manager) {
	 auto window_size = Engine::get_instance()->get_window_size();
	 constexpr Vector2 size = { 250, 0 };
	 ImVec2 pos = { window_size.x - size.x, 25 };
	 ImGui::SetNextWindowPos({ pos });
	 ImGui::SetNextWindowSize({ size.x, size.y });
	 ImGui::Begin("PropertiesWindow", nullptr, ImGuiWindowFlags_NoDecoration);
	 scene_tree.render();
	 properties_panel.render(geometry_manager);
	 ImGui::End();
}