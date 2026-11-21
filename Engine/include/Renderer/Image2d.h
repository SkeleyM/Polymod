#pragma once

#include <vector>
#include <filesystem>
#include <memory>

constexpr int PNG_COMPRESSION_LEVEL_DEFAULT = 8;
constexpr int PNG_COMPRESSION_LEVEL_MAX = 9;

struct Image2d {
	std::vector<uint8_t> data;
	uint32_t width{ (uint32_t)(-1) };
	uint32_t height{ (uint32_t)(-1) };
	uint32_t channels{ (uint32_t)(-1) };
	
	static std::shared_ptr<Image2d> from_image_file(std::filesystem::path path);
	static std::vector<uint8_t> to_png_bytes(std::shared_ptr<Image2d> image, uint8_t compression_level = PNG_COMPRESSION_LEVEL_DEFAULT);
};