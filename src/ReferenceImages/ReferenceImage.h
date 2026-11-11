#pragma once
#include <Renderer/Mesh.h>
#include <Renderer/Image2d.h>

#include <vector>
#include <memory>
#include <string>

struct ReferenceImage {
	std::string name;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(nullptr, 0);

	// Save the image, the engine discards it after loading it into a texture.
	// But its needed to be able to save the reference image to a file.
	Image2d image;

	ReferenceImage(std::string name, Image2d image) {
		this->name = name;

		// Apply a shrink factor so the image is not extremely huge in world units
		// Uses standard screen image width of 1920, but halved
		const float shrink_factor = 1.0f / (1920.0f);
		float scalefactorX = (float)image.width * shrink_factor;
		float scalefactorY = (float)image.height * shrink_factor;
		

		Triangle triangles[] = {
			Triangle(
				Vector3(-0.5f * scalefactorX, -0.5f * scalefactorY, 0.0f),
				Vector3(0.5f * scalefactorX, 0.5f * scalefactorY, 0.0f),
				Vector3(-0.5f * scalefactorX, 0.5f * scalefactorY, 0.0f)
			),
			Triangle(
				Vector3(-0.5f * scalefactorX, -0.5f * scalefactorY, 0.0f),
				Vector3(0.5f * scalefactorX, 0.5f * scalefactorY, 0.0f),
				Vector3(0.5f * scalefactorX, -0.5f * scalefactorY, 0.0f)
			),
		};
		triangles[0].vertices[0].texture = Vector2(1.0f, 1.0f);
		triangles[0].vertices[1].texture = Vector2(0.0f, 0.0f);
		triangles[1].vertices[0].texture = Vector2(1.0f, 1.0f);
		triangles[1].vertices[1].texture = Vector2(0.0f, 0.0f);

		triangles[0].vertices[2].texture = Vector2(1.0f, 0.0f);
		triangles[1].vertices[2].texture = Vector2(0.0f, 1.0f);


		auto mesh = std::make_shared<Mesh>(triangles, 2);

		Texture texture = Texture::from_rgb_bytes(image.data.data(), image.width, image.height, image.channels);
		mesh->texture = texture;

		this->image = image;
		this->mesh = mesh;
	}

	const std::shared_ptr<Mesh> get_mesh() const {
		return mesh;
	}
};