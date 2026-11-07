#include <glad/glad.h>
#include <Renderer/Texture.h>

#include <Renderer/Image2d.h>

Texture Texture::from_image_file(std::filesystem::path path) {
	Image2d image = Image2d::from_image_file(path);
	return from_rgb_bytes(image.data.data(), image.width, image.height);
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