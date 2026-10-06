#pragma once

#include <Geometry/Formats/AbstractGeometryFormat.h>

#include <filesystem>
#include <optional>

namespace GeometryFormat {
    namespace GeometryFileHandler {
        std::optional<Geometry> import_geometry(AbstractGeometryFormat* format, std::string source);
        void export_geometry(AbstractGeometryFormat* format, Geometry geometry, std::filesystem::path path, std::string name);
    };
}