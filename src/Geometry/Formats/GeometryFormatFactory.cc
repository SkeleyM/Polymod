#include <Geometry/Formats/GeometryFormatFactory.h>

#include <Geometry/Formats/PolymodelGeometry.h>
#include <Geometry/Formats/WavefrontObj.h>

std::unique_ptr<GeometryFormat::AbstractGeometryFormat> GeometryFormat::GeometryFormatFactory::create_format(GeometryFormat::GeometryFormatSpec spec) {
    switch (spec.geometry_format)
    {
    case (GeometryFormatType::Polymodel): {
        abort();
        break;
    }
    case (GeometryFormatType::WavefrontObj): {
        return std::make_unique<WavefrontObj>(spec);
        break;
    }
    default:
        // Invalid format type somehow.
        abort();
        break;
    }
}