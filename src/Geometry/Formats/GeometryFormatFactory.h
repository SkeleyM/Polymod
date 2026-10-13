#pragma once

#include <Geometry/Formats/AbstractGeometryFormat.h>

#include <memory>

namespace GeometryFormat {
    class GeometryFormatFactory {
    public:
        std::unique_ptr<AbstractGeometryFormat> create_format(GeometryFormatSpec spec);
    };
}