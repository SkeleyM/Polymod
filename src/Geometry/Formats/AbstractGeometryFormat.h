#pragma once

#include <Geometry/Geometry.h>
#include <Geometry/Formats/GeometryFormatSpec.h>

#include <string>
#include <optional>

namespace GeometryFormat {
    class AbstractGeometryFormat {
    protected:
        GeometryFormatSpec spec;
    public:
        Geometry preprocess_geometry_with_spec(Geometry);
        virtual std::string serialize(Geometry) = 0;
        virtual std::optional<Geometry> deserialize(std::string) = 0;
    };
}