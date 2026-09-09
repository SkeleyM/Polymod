#pragma once

#include <Renderer/PointRenderer.h>
#include <Renderer/LineRenderer.h>
#include <Geometry/Geometry.h>
#include <Geometry/Operations/AbstractGeometryOperation.h>

class GeometryWireframeRenderer {
private:
    LineRenderer edge_renderer;
    PointRenderer vertex_renderer;
public:
    void set_edge_size(float size);
    void set_vertex_size(float size);
    void render_wireframe(Geometry& geometry, SelectedGeometry& highlight_selection);
};