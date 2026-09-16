#pragma once

#include <Geometry/Geometry.h>

#include <string>

namespace GeometryFormats {
    namespace WavefrontObj {
            std::string serialize(Geometry& geometry);
            Geometry deserialize(const std::string& source);
            void export_file(Geometry& geometry, std::string& file); 
            Geometry export_file(const std::string& file); 
    };
}