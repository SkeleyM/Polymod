#pragma once

#include <vector>
#include <filesystem>

struct Image2d {
	std::vector<uint8_t> data;
	uint32_t width;
	uint32_t height;
	uint32_t channels;

	static Image2d from_image_file(std::filesystem::path path);
};