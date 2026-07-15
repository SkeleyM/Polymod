#include <Scene.h>

Scene::Scene() {}

Scene::~Scene() {}

void Scene::render() {
	for (int i = 0; i < this->meshes.size(); i++) {
		auto mesh = this->meshes.at(i);
		this->renderer.render(this->camera, &mesh);
	}
}

void Scene::add_mesh(Mesh mesh) {
	this->meshes.push_back(mesh);
}