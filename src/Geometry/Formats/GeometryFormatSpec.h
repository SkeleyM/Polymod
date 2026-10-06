#pragma once

namespace GeometryFormat {
    enum class GeometryFormatType {
        Polymodel,
        WavefrontObj,
    };

    struct GeometryFormatSpec {
        bool include_vertex_normals{ true };
        bool include_vertex_colours{ true };
        bool triangulate_geometry{ false };
        bool apply_transform{ true };

        bool center_of_geometry_as_model_origin{ false };

        GeometryFormatType geometry_format { GeometryFormatType::Polymodel };
    };
}