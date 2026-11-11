#pragma once

#include <ReferenceImage.h>

#include <vector>
#include <filesystem>

struct ReferenceImageManager {
private:
	std::vector<ReferenceImage> reference_images;
public:
	ReferenceImage& create_reference_image(std::string name, std::filesystem::path image_path);
	void delete_reference_image(std::string name);
	const std::vector<ReferenceImage>& get_reference_images() { return reference_images; }
};