#include <Renderer/Image2d.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

std::shared_ptr<Image2d> Image2d::from_image_file(std::filesystem::path path) {
	uint32_t width{ 0 }, height{ 0 }, channels{ 0 };

	auto image = stbi_load(path.string().c_str(), (int*)&width, (int*)&height, (int*)&channels, 0);
	std::vector<uint8_t> data(width * height * channels);

	// Almost 100% not a good idea
	std::memcpy(data.data(), image, width * height * channels);
	// Free image data loaded by stbi, since we copied it into our own vector
	stbi_image_free(image);

	return std::make_shared<Image2d>(Image2d{ data, width, height, channels });
}

std::vector<uint8_t> Image2d::to_png_bytes(std::shared_ptr<Image2d> image, uint8_t compression_level) {
	int32_t png_data_size{ 0 };

	// Set compression level
	if (compression_level > PNG_COMPRESSION_LEVEL_MAX) 
		compression_level = PNG_COMPRESSION_LEVEL_MAX;
	stbi_write_png_compression_level = compression_level;

	uint8_t* png_bytes = stbi_write_png_to_mem(
		image->data.data(), 
		0, 
		image->width, 
		image->height, 
		image->channels, 
		&png_data_size
	);

	std::vector<uint8_t> data(png_data_size);
	std::memcpy(data.data(), png_bytes, png_data_size);
	stbi_image_free(png_bytes);

	return data;
}