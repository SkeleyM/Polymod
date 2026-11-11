#include <ReferenceImageManager.h>

#include <Renderer/Image2d.h>
#include <Renderer/Texture.h>
#include <Engine.h>

ReferenceImage& ReferenceImageManager::create_reference_image(std::string name, std::filesystem::path image_path) {
	Image2d image = Image2d::from_image_file(image_path.string());
	ReferenceImage reference = ReferenceImage(name, image);

	// Place its mesh in the scene
	auto engine = Engine::get_instance();
	auto& scene = engine->get_active_scene();
	scene.add_mesh(*reference.get_mesh());

	reference_images.push_back(reference);
	return reference_images.back();
}

void ReferenceImageManager::delete_reference_image(std::string name) {
	for (auto image = this->reference_images.begin(); image != this->reference_images.end(); image++) {
		if (image->name == name) {
			this->reference_images.erase(image);
			auto engine = Engine::get_instance();
			auto& scene = engine->get_active_scene();
			scene.remove_mesh(image->get_mesh()->id);
		}
	}
}
