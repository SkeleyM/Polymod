#pragma once

#include <Geometry/Formats/AbstractGeometryFormat.h>

namespace GeometryFormat {
    class WavefrontObj : public AbstractGeometryFormat {
    public:
        WavefrontObj(GeometryFormatSpec spec) {
            this->spec = spec;
        } 
        
        std::string serialize(Geometry geometry);
        std::optional<Geometry> deserialize(std::string source);
    };
}