#include <Renderer/Image2d.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image2d Image2d::from_image_file(std::filesystem::path path) {
	uint32_t width{ 0 }, height{ 0 }, channels{ 0 };

	auto image = stbi_load(path.string().c_str(), (int*)&width, (int*)&height, (int*)&channels, 0);
	std::vector<uint8_t> data(width * height * channels);

	// Almost 100% not a good idea
	std::memcpy(data.data(), image, width * height * channels);

	return Image2d{ data, width, height, channels };
}