#pragma once

#include <Geometry/Geometry.h>
#include <Geometry/Formats/GeometryFormatSpec.h>

#include <string>

namespace GeometryFormat {
    class AbstractGeometryFormat {
    protected:
        GeometryFormatSpec spec;
    public:
        Geometry preprocess_geometry_with_spec(Geometry);
        virtual std::string serialize(Geometry) = 0;
        virtual Geometry deserialize(std::string) = 0;
    };
}