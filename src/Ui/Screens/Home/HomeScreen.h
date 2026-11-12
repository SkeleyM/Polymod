#include <Engine.h>

#include <PolymodProject/PolymodProject.h>
#include <PolymodProject/RecentProjects.h>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <Ui/UiConstants.h>

#include <nfd.h>

#include <functional>
#include <filesystem>
#include <map>

namespace Polymodel::Screens {
	class HomeScreen {
	private:
		enum class HomeScreenState {
			Home,
			ChoosingProjectName,
		};
		HomeScreenState state = HomeScreenState::Home;

		std::function<void(std::filesystem::path, std::string)> on_new_project_callback;
		std::function<void(std::filesystem::path)> on_open_project_callback;

		std::unordered_map<std::filesystem::path, Polymodel::Project::ProjectMetadata> cached_metadata;

		std::string name;

		void show_name_picker() {
			Engine* engine = Engine::get_instance();
			auto window_size = engine->get_window_size();

			ImGui::Begin("Name Picker", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowPos({ 0, 0 });
			ImGui::SetWindowSize({ window_size.x, window_size.y });

			ImGui::PushStyleColor(ImGuiCol_ChildBg, COLOUR_CONST_SECONDARY);

			ImVec2 dialog_size = { 300.0f, 200.0f };
			auto avail = ImGui::GetContentRegionAvail();
			auto new_pos = ImVec2((avail.x - dialog_size.x) * 0.5, (avail.y - dialog_size.y) * 0.5);
			ImGui::SetCursorPos(new_pos);

			ImGui::BeginChild("Name Picker Dialog", dialog_size, true);

			ImGui::InputText("Project Name", &this->name);
			if (ImGui::Button("Done")) {
				nfdu8char_t* save_path;
				nfdu8char_t* default_path = "Documents/";
				auto pick_result = NFD_PickFolder(&save_path, default_path);

				if (pick_result == NFD_OKAY) {
					auto path = std::filesystem::path(save_path);
					this->on_new_project_callback(path / this->name, this->name);
					this->state = HomeScreenState::Home;
					this->name.clear();
				}
			}

			ImGui::EndChild();
			ImGui::PopStyleColor();
			ImGui::End();
		}

		Polymodel::Project::ProjectMetadata read_project_metadata(std::filesystem::path path) {
			if (this->cached_metadata.find(path) == this->cached_metadata.end()) {
				auto metadata = Polymodel::Project::read_metadata(path);
				this->cached_metadata[path] = metadata;
				return metadata;
			}
			return this->cached_metadata[path];
		}

		bool project_button(std::filesystem::path path) {
			auto id = "Project button " + path.filename().string();

			auto project_name = path.filename().string();
			auto metadata = this->read_project_metadata(path);

			auto time = static_cast<const std::time_t>(metadata.last_accessed);

			auto format = "%d-%m-%y %H:%M";
			char time_buffer[64] = {};
			std::strftime(time_buffer, 64, format, std::localtime(&time));

			ImGui::BeginChild(id.c_str(), {300.0f, 0.0}, ImGuiChildFlags_Borders);
			const bool clicked = ImGui::IsWindowHovered(ImGuiHoveredFlags_None)
				&& ImGui::IsMouseClicked(ImGuiMouseButton_Left);

			ImGui::Text(project_name.c_str());
			ImGui::Text("Last accessed: %s", time_buffer);
			ImGui::EndChild();

			return clicked;
		}

		void show_home_screen(Polymodel::Project::RecentProjects& recent_projects) {
			Engine* engine = Engine::get_instance();
			auto window_size = engine->get_window_size();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 50.0f, 50.0f });
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 100.0f });

			ImGui::Begin("Home", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowPos({ 0, 0 });
			ImGui::SetWindowSize({ window_size.x, window_size.y });
			ImGui::SetWindowFocus();

			ImGui::SetWindowFontScale(2.0f);
			// Transition to choosing project name state
			if (ImGui::Button("New Project", { 220.0f, 60.0f }))
				this->state = HomeScreenState::ChoosingProjectName;
			ImGui::SetWindowFontScale(1.0f);

			ImGui::PopStyleVar();

			// Render the previous projects
			ImGui::Text("Previous Projects");
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 100.0f });
			ImGui::BeginChild("Previous Projects", { 0, 300.0 }, ImGuiChildFlags_Borders);

			ImGui::PopStyleVar();

			int iter = 0;
			for (auto& prev_project : recent_projects.get_recent_project_paths()) {
				if (iter >= 3) break;
				if (this->project_button(prev_project)) {
					this->on_open_project_callback(prev_project);
				}
				ImGui::SameLine();
				iter++;
			}
			
			ImGui::EndChild();
			ImGui::End();
			ImGui::PopStyleVar(2);
		}
	public:
		HomeScreen(
			std::function<void(std::filesystem::path, std::string)> on_new_project_callback,
			std::function<void(std::filesystem::path)> on_open_project_callback
		) : on_new_project_callback(on_new_project_callback), on_open_project_callback(on_open_project_callback) {}

		void render(Polymodel::Project::RecentProjects& recent_projects) {
			switch (this->state) {
				case (HomeScreenState::Home): {
					this->show_home_screen(recent_projects);
					break;
				}
				case (HomeScreenState::ChoosingProjectName): {
					this->show_name_picker();
					break;
				}
			}
		}
	};
}