#pragma once

#include <Renderer/Image2d.h>
#include <Renderer/Texture.h>
#include <EMath.h>

#include <string>
#include <optional>

// For creation and serialisation of materials
struct MaterialSpec {
	std::string name{ "Material" };
	bool use_texture_image_transparency{ true }; // UNUSED FIX
	std::optional<std::shared_ptr<Image2d>> texture{ std::nullopt };
	bool use_albedo_colour{ true };
	Vector4 albedo_colour{ 1.0f, 1.0f, 1.0f, 1.0f };

	static std::string deserialize(MaterialSpec source_material);
	static std::optional<MaterialSpec> deserialize(std::string source);
};

// Defines a runtime material
struct Material {
	std::string material_name{ "Material" };

	bool use_texture{ false }; // Passed to shader, false if null texture
	std::shared_ptr<Texture> texture;

	bool use_albedo_colour{ true };
	Vector4 albedo_colour{ 1.0f, 1.0f, 1.0f, 1.0f };

private:
	Material(std::string name);
public:
	static std::shared_ptr<Material> create_default(std::string name);
	static std::shared_ptr<Material> from_material_spec(MaterialSpec specification);
};