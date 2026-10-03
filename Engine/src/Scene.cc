#include <Scene.h>

Scene::Scene() {
}

Scene::~Scene() {}

void Scene::render() {
	this->renderer.get_shader().set_uniform_vector3("light_position", this->light.position);
	this->renderer.get_shader().set_uniform_vector3("light_colour", this->light.colour);

	for (int i = 0; i < this->meshes.size(); i++) {
		Mesh& mesh = this->meshes[i];
		this->renderer.render(this->camera, &mesh);
	}
}

void Scene::add_mesh(Mesh mesh) {
	this->meshes.push_back(mesh);
}

void Scene::remove_mesh(int id) {
	for (int i = 0; i < this->meshes.size(); i++) {
		Mesh& mesh = this->meshes[i];
		if (mesh.id == id) {
			Mesh& mesh = *(this->meshes.begin() + i);
			this->renderer.delete_mesh_from_buffer(mesh);
			this->meshes.erase(this->meshes.begin() + i);
			i--;
		}
	}
}

void Scene::clear_scene() {
	this->meshes.clear();
}