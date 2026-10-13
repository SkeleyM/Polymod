#pragma once

#include <Geometry/Formats/AbstractGeometryFormat.h>

#include <filesystem>
#include <optional>

namespace GeometryFormat {
    namespace GeometryFileHandler {
        std::optional<Geometry> import_geometry(GeometryFormat::AbstractGeometryFormat* format, std::filesystem::path path);
        bool export_geometry(AbstractGeometryFormat* format, Geometry geometry, std::filesystem::path path);
    };
}