#include <Geometry/Formats/WavefrontObj.h>

#include <filesystem>
#include <fstream>

std::string GeometryFormats::WavefrontObj::serialize(Geometry& geometry) {
    // Create the vertex table
    std::string vertex_table = {};

    auto all_ids = geometry.get_all_vertex_ids();
    for (int i = 0; i < all_ids.size(); i++) {
        Vertex& v = geometry.get_vertex(i);
        vertex_table.append("v " + 
            std::to_string(v.position.x) + ' ' +
            std::to_string(v.position.y) + ' ' +
            std::to_string(v.position.z) + '\n'
        );
    }

    // Create the face table
    std::string face_table = {};

    auto all_faces = geometry.get_faces();
    for (int f = 0; f < all_faces.size(); f++) {
        Face& face = all_faces.at(f);
        face_table.append("f ");
        for (int v = 0; v < face.vertices.size(); v++) {
            // add one since obj indicies begin at 1 not 0
            int v_id = face.vertices[v] + 1;
            face_table.append(std::to_string(v_id) + ' ');
        }
        face_table.append("\n");
    }

    return vertex_table + face_table;
}

Geometry GeometryFormats::WavefrontObj::deserialize(const std::string& source) {
    Geometry geometry;

    // Split the string into new lines
    std::vector<std::string> segments;
    std::string segment;
    std::stringstream source_stream (source);
    while (std::getline(source_stream, segment, '\n')) {
        segments.push_back(segment);
    }

    return {};
}

void GeometryFormats::WavefrontObj::export_file(Geometry& geometry, std::string& path) {
    std::ofstream file(path);
    file.clear();

    std::string serialized = GeometryFormats::WavefrontObj::serialize(geometry);
    file << serialized.c_str();
}

Geometry GeometryFormats::WavefrontObj::export_file(const std::string& file) {
    return {};
}
