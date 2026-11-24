#include <Renderer/Material.h>

std::string MaterialSpec::deserialize(MaterialSpec source_material) {
	abort();
}

std::optional<MaterialSpec> MaterialSpec::deserialize(std::string source) {
	abort();
}

Material::Material(std::string name) {
	this->material_name = name;
}

std::shared_ptr<Material> Material::create_default(std::string name) {
	MaterialSpec spec;
	spec.name = name;

	auto material = Material::from_material_spec(spec);
	return material;
}

std::shared_ptr<Material> Material::from_material_spec(MaterialSpec specification) {
	Material* mat_ptr = new Material(specification.name);
	std::shared_ptr<Material> material = std::shared_ptr<Material>(mat_ptr);
	
	material->use_texture = specification.texture.has_value();
	// Generate a texture from the spec's image if it has one
	if (specification.texture.has_value()) {
		material->texture = Texture::from_image2d(specification.texture.value());
	}

	material->use_albedo_colour = specification.use_albedo_colour;
	material->albedo_colour = specification.albedo_colour;

	return material;
}