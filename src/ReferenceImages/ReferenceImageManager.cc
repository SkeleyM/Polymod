#include <ReferenceImageManager.h>

#include <Renderer/Image2d.h>
#include <Renderer/Texture.h>
#include <Engine.h>

std::shared_ptr<ReferenceImage> ReferenceImageManager::create_reference_image(std::string name, std::filesystem::path image_path) {
	auto image = Image2d::from_image_file(image_path.string());
	auto reference = std::make_shared<ReferenceImage>(name, image);

	// Place its mesh in the scene
	auto engine = Engine::get_instance();
	auto& scene = engine->get_active_scene();
	scene.add_mesh(reference->get_mesh());

	reference_images.push_back(reference);
	return reference_images.back();
}

void ReferenceImageManager::delete_reference_image(std::string name) {
	for (auto image = this->reference_images.begin(); image != this->reference_images.end(); image++) {
		if (image->get()->name == name) {
			// Remove mesh from scene
			auto engine = Engine::get_instance();
			auto& scene = engine->get_active_scene();
			scene.remove_mesh(image->get()->get_mesh());

			this->reference_images.erase(image);
		}
	}
}
