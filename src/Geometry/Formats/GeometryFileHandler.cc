#include <Geometry/Formats/GeometryFileHandler.h>

#include <fstream>
#include <iostream>

std::optional<Geometry> GeometryFormat::GeometryFileHandler::import_geometry(GeometryFormat::AbstractGeometryFormat* format, std::string source) {
    return std::nullopt;
}

void GeometryFormat::GeometryFileHandler::export_geometry(GeometryFormat::AbstractGeometryFormat* format, Geometry geometry, std::filesystem::path path, std::string name) {
    // If parent folder does not exist, then we cannot make a file there
    path = std::filesystem::canonical(path);
    std::cout << "saving at " << path / name << std::endl;
    if (path.has_parent_path() && !std::filesystem::exists(path.parent_path())) {
        std::cerr << "Geometry export path does not exist" << std::endl;
        return;
    }

    std::ofstream file(path / name, std::ios::out);
    if (!file) {
        std::cerr << "Failed to create or open file for exporting" << std::endl;
        return;
    }

    file << format->serialize(geometry);
    file.close();
}