#pragma once

#include <vector>
#include <filesystem>
#include <memory>

struct Image2d {
	std::vector<uint8_t> data;
	uint32_t width{ (uint32_t)(-1) };
	uint32_t height{ (uint32_t)(-1) };
	uint32_t channels{ (uint32_t)(-1) };
	
	static std::shared_ptr<Image2d> from_image_file(std::filesystem::path path);
};