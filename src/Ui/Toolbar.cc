#include <Ui/Toolbar.h>
#include <InputManager.h>

#include <imgui.h>

Toolbar::Toolbar(std::function<void(ToolbarTool*)> on_tool_click) {
	this->on_tool_click = on_tool_click;
}

void Toolbar::render() {
	if (this->collapsed) {
		this->render_collapse();
		return;
	}

	ImGui::Begin(
		"Toolbar", 
		&this->collapsed, 
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration
	);
	ImGui::SetWindowPos({0.0f, (1080 - 600) / 2});
	ImGui::SetWindowSize({ TOOLBAR_SIZE.x, TOOLBAR_SIZE.y });

	this->render_collapse();

	for (ToolbarTool* tool : this->tools) {
		if (ImGui::Button(tool->get_name().c_str(), {55.0f, 55.0f})) {
			this->on_tool_click(tool);
		}
		if (ImGui::IsItemHovered()) {
			this->render_tooltip(tool);
		}
	}
	
	ImGui::End();
}

void Toolbar::render_tooltip(ToolbarTool* tool) {
	InputManager& input = InputManager::get();
	Vector2 mouse_pos = input.get_mouse_pos();

	ImGui::SetNextWindowPos({TOOLBAR_SIZE.x, mouse_pos.y});
	ImGui::SetNextWindowSize({250.0f, 50.0f});
	ImGui::Begin("Tooltip", nullptr, ImGuiWindowFlags_NoDecoration);
	ImGui::TextWrapped(tool->get_tooltip().c_str());
	ImGui::End();
}

void Toolbar::render_collapse() {
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	
	// Change text and position depending on if the toolbar is collapsed
	char button_text[2] = { this->collapsed ? '>' : '<', '\0' };
	float collapse_button_y_pos = 240.0f;
	float collapse_button_x_pos = this->collapsed ? 0.0f : TOOLBAR_SIZE.x;

	ImGui::SetNextWindowSize({ 1.0f, 1.0f });
	ImGui::SetNextWindowPos({ collapse_button_x_pos, collapse_button_y_pos });
	ImGui::Begin(
		"Collapse_Button",
		&this->collapsed,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration
	);


	// Render collapse control button
	if (ImGui::Button(button_text, { 31.0f, 31.0f })) {
		this->collapsed = !this->collapsed;
	}

	ImGui::PopStyleVar();


	ImGui::End();
}

void Toolbar::collapse() {
	this->collapsed = true;
}

void Toolbar::expand() {
	this->collapsed = false;
}

void Toolbar::add_tool(ToolbarTool* tool) {
	this->tools.push_back(tool);
}

void Toolbar::simulate_tool_click(ToolbarTool* tool) {
	this->on_tool_click(tool);
}