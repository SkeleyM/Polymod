#include <Geometry/Formats/GeometryFileHandler.h>

#include <fstream>
#include <sstream>
#include <iostream>

std::optional<Geometry> GeometryFormat::GeometryFileHandler::import_geometry(GeometryFormat::AbstractGeometryFormat* format, std::filesystem::path path) {
    if (!std::filesystem::exists(path)) {
        return std::nullopt;
    }

    std::stringstream source;
    std::ifstream file(path);

    source << file.rdbuf();

    return format->deserialize(source.str());
}

bool GeometryFormat::GeometryFileHandler::export_geometry(GeometryFormat::AbstractGeometryFormat* format, Geometry geometry, std::filesystem::path path) {
    // If parent folder does not exist, then we cannot make a file there
    std::cout << "saving at " << path << std::endl;
    if (path.has_parent_path() && !std::filesystem::exists(path.parent_path())) {
        std::cerr << "Geometry export path does not exist" << std::endl;
        return false;
    }

    std::ofstream file(path, std::ios::out);
    if (!file) {
        std::cerr << "Failed to create or open file for exporting" << std::endl;
        return false;
    }

    file << format->serialize(geometry);
    file.close();

    return true;
}