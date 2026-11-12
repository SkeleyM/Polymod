#include <Ui/GeometryEditor/SideWindow.h>

#include <Engine.h>

void SideWindow::render() {
	 auto window_size = Engine::get_instance()->get_window_size();
	 constexpr Vector2 size = { 250, 0 };
	 ImVec2 pos = { window_size.x - size.x, 25 };
	 ImGui::SetNextWindowPos({ pos });
	 ImGui::SetNextWindowSize({ size.x, size.y });
	 ImGui::Begin("PropertiesWindow", nullptr, ImGuiWindowFlags_NoDecoration);
	 scene_tree.render();
	 properties_panel.render();
	 ImGui::End();
}