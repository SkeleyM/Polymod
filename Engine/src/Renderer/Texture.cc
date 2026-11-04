#include <glad/glad.h>
#include <Renderer/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture Texture::from_image_file(std::filesystem::path path) {
	uint32_t width{ 0 }, height { 0 }, channels { 0 };

	auto image = stbi_load(path.string().c_str(), (int*)&width, (int*)&height, (int*)&channels, 0);
	return from_rgb_bytes(image, width, height);
}

Texture Texture::from_rgb_bytes(uint8_t* data, uint32_t width, uint32_t height) {
	Texture texture;
	texture.gl_texture_id = -1;

	glGenTextures(1, &texture.gl_texture_id);
	glBindTexture(GL_TEXTURE_2D, texture.gl_texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	return texture;
}