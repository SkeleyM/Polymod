#include <Scene.h>

Scene::Scene() {
}

Scene::~Scene() {}

void Scene::render() {
	this->renderer.get_shader().set_uniform_vector3("light_position", this->light.position);
	this->renderer.get_shader().set_uniform_vector3("light_colour", this->light.colour);

	static float t = 0;
	for (int i = 0; i < this->meshes.size(); i++) {
		auto mesh = this->meshes.at(i);
		this->renderer.render(this->camera, &mesh);
	}
}

void Scene::add_mesh(Mesh mesh) {
	this->meshes.push_back(mesh);
}