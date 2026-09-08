#pragma once
#include <EMath.h>
#include <Scene.h>
#include <Renderer/TriangleRenderer.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Engine {
private:
	static Engine* engine_instance;

	Scene* main_scene;

	// Required to store window size to calculate aspect ratio for rendering
	Vector2 window_size;
	GLFWwindow* window;

	std::function<void()> on_load_callback;
	std::function<void()> on_render_callback;
public:
	Engine(const char* window_title, int width, int height);
	~Engine();

	static Engine* get_instance() { return Engine::engine_instance; }
	static void clear_framebuffer(Vector3 clear_colour);

	Scene& get_active_scene() { return *this->main_scene; }
	float get_aspect_ratio() { return window_size.x / window_size.y; }
	Vector2 get_window_size() { return this->window_size; }

	bool should_keep_ticking();
	void tick();

	void set_on_load(std::function<void()> callback) {
		this->on_load_callback = callback;
	}

	void set_on_render(std::function<void()> callback) {
		this->on_render_callback = callback;
	}
};