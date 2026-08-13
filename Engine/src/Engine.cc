#include <Engine.h>
#include <InputManager.h>

#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>
#include <Renderer/Mesh.h>
#include <Renderer/Shader.h>
#include <Renderer/Meshbuffer.h>
#include <imgui_impl/ImGui.h>

#include <iostream>

Engine* Engine::engine_instance = nullptr;

void dummy_callback() {}

Engine::Engine(const char* window_title, int width, int height) {
	if (!glfwInit()) {
		glfwTerminate();
		std::cerr << "Failed to initialise GLFW" << std::endl;
	}
	this->window = glfwCreateWindow(width, height, window_title, NULL, NULL);
	if (!this->window) {
		glfwTerminate();
		std::cerr << "Failed to initialise Window" << std::endl;
	}

	glfwMakeContextCurrent(this->window);
	// Enable Vsync
	glfwSwapInterval(0);

	// Initialise glad to load specified OpenGL version (3.3 core)
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);

	glfwSetScrollCallback(this->window, glfw_scroll_handler);
	glfwSetCursorPosCallback(this->window, glfw_mouse_handler);
	glfwSetKeyCallback(this->window, glfw_key_handler);

	Engine::engine_instance = this;
	this->window_size = Vector2((float)width, (float)height);

	this->on_load_callback = dummy_callback;
	this->on_render_callback = dummy_callback;

	this->main_scene = new Scene();

	// Initialise ImGui
	ImguiWrapper::gl_glfw_imgui_init(this->window);
}

// Destroy resources and safely shut down glfw
Engine::~Engine() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
}	

void Engine::clear_framebuffer(Vector3 clear_colour) {
	// Clear the screen
	glClearColor(clear_colour.x, clear_colour.y, clear_colour.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Engine::should_keep_ticking() {
	return !glfwWindowShouldClose(this->window);
}

void Engine::tick() {
	ImguiWrapper::gl_glfw_imgui_new_frame();

	glfwPollEvents();

	this->clear_framebuffer(Vector3(0.2f, 0.2f, 0.2f));
	this->main_scene->render();
	this->on_render_callback();

	ImguiWrapper::gl_render();

	glfwSwapBuffers(this->window);

	// Reset some input
	InputManager& input_manager = InputManager::get();
	input_manager._reset_scroll();

}

bool Engine::get_left_mouse() {
	return glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
}