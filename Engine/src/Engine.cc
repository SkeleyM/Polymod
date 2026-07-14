#include <Engine.h>

#include <Renderer/Triangle.h>
#include <Renderer/Vertex.h>
#include <Renderer/Mesh.h>
#include <Renderer/Shader.h>
#include <Renderer/Meshbuffer.h>
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

	// Enable Vsync
	glfwSwapInterval(1);
	glfwMakeContextCurrent(this->window);

	// Initialise glad to load specified OpenGL version (3.3 core)
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glViewport(0, 0, width, height);

	Engine::engine_instance = this;
	this->window_size = Vector2((float)width, (float)height);
	this->on_load_callback = dummy_callback;
	this->on_render_callback = dummy_callback;

	this->main_scene = new Scene();
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
	glfwPollEvents();

	this->clear_framebuffer(Vector3(0.2f, 0.2f, 0.2f));
	this->main_scene->render();
	this->on_render_callback();

	glfwSwapBuffers(this->window);
}