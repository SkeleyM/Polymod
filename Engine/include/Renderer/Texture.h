#pragma once
#include <EMath.h>

#include <filesystem>

struct Texture {
	uint32_t width{ 0 };
	uint32_t height{ 0 };

	uint32_t gl_texture_id{ (uint32_t)(-1) };

	static Texture from_image_file(std::filesystem::path path);
	static Texture from_rgb_bytes(uint8_t* data, uint32_t width, uint32_t height, uint8_t channels);
};