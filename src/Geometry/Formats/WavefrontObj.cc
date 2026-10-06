#include <Geometry/Formats/WavefrontObj.h>

#include <sstream>

std::string GeometryFormat::WavefrontObj::serialize(Geometry geometry) {
    std::stringstream serialised;

    auto all_ids = geometry.get_all_vertex_ids();

    // Build the vertex table
    for (int v = 0; v < all_ids.size(); v++) {
        Vertex& vertex = geometry.get_vertex(all_ids[v]);

        serialised << "v "
            << vertex.position.x << ' '
            << vertex.position.y << ' '
            << vertex.position.z << std::endl;
    }

    // Build the normal table, if enabled
    if (this->spec.include_vertex_normals)
    for (int v = 0; v < all_ids.size(); v++) {
        Vertex& vertex = geometry.get_vertex(all_ids[v]);

        serialised << "vn "
            << vertex.normal.x << ' '
            << vertex.normal.y << ' '
            << vertex.normal.z << std::endl;
    }

    // Build the face table
    auto& all_faces = geometry.get_faces();
    for (int f = 0; f < all_faces.size(); f++) {
        Face& face = all_faces[f];

        serialised << "f ";
        for (int v = 0; v < face.vertices.size(); v++) {
            // Offset id's by one because obj begins indexing at 1 not 0
            uint32_t v_id = face.vertices[v] + 1;
            serialised << v_id << "//" << v_id << ' ';
        }
        serialised << std::endl;
    }

    return serialised.str();
}

Vector3 read_vector3_from_line(std::string line, size_t offset) {
    float f[] = {0.0f, 0.0f, 0.0f};
    size_t current_float = 0;

    while (line.size() > offset) {
        size_t decimal_start = offset;
        while (line[offset] != ' ' && line.size() > offset) 
            offset++;
        std::string float_str = line.substr(decimal_start, offset-decimal_start);
        offset++;
        
        f[current_float++] = std::atof(float_str.c_str());
    }
    return {f[0], f[1], f[2]};
}

struct face_ids {
    int position{ -1 };
    int texture{ -1 };
    int normal{ -1 };
};

std::vector<face_ids> read_face(std::string line, size_t offset) {
    std::vector<std::string> vert_entries;
    while (line.size() > offset) {
        size_t entry_start = offset;
        while (line.size() > offset && line[offset] != ' ')
            offset++;
        auto substr = line.substr(entry_start, offset-entry_start);
        vert_entries.push_back(substr);
        offset++;
    }

    std::vector<face_ids> ids;

    for (auto& vert_entry : vert_entries) {
        // Read position
        size_t offset = 0;
        size_t id_pos = vert_entry.find('/');
        std::string pos_string = vert_entry.substr(0, id_pos);
        int position = std::atoi(pos_string.c_str()) - 1; 

        // Read texture
        offset = id_pos + 1;
        id_pos = vert_entry.find('/', offset);
        // No more ids to read
        if (id_pos == std::string::npos) {
            ids.push_back({position, -1, -1});
            continue;
        }
        std::string texture_string = vert_entry.substr(offset, id_pos-offset);
        int texture;
        // If they are the same, then the string looks like 'a//b', which omits the texture coordinate
        if (id_pos == offset) {
            texture = -1;
        }
        else {
            texture = std::atoi(texture_string.c_str()) - 1;
        }

        // Read normal
        // If theres no more ids then it is omitted
        if (offset >= vert_entry.size()) {
            ids.push_back({ position, texture, -1 });
            continue;
        }
        offset = id_pos + 1;
        id_pos = vert_entry.find('/', id_pos+1);
        // No more ids to read
        std::string normal_string = vert_entry.substr(offset, id_pos-offset);
        int normal = std::atoi(normal_string.c_str()) - 1; 
        ids.push_back({position, texture, normal});
    }

    return ids;
}

std::optional<Geometry> GeometryFormat::WavefrontObj::deserialize(std::string source) {
    Geometry geometry;

    std::stringstream source_stream(source);
    std::string current_line;

    std::vector<Vector3> normals;

    while (std::getline(source_stream, current_line)) {
        size_t index = 0;
        if (current_line[index] == 'v') {
            index++;
            // vertex pos
            if (current_line[index] == ' ') {
                Vector3 position_vector = read_vector3_from_line(current_line, ++index);
                geometry.add_vertex(position_vector);
            }
            // vertex normal
            if (current_line[index] == 'n') {
                index++;
                Vector3 normal_vector = read_vector3_from_line(current_line, ++index);
                normals.push_back(normal_vector);
            } else continue;
        }
        if (current_line[index] == 'f') {
            index += 2;
            auto ids = read_face(current_line, index);

            std::vector<int> vertex_ids;
            vertex_ids.reserve(ids.size());

            // Set all the normals
            for (auto& id : ids) {
                // Invalid vertex id
                if (id.position > geometry.get_vertex_count()) {
                    return std::nullopt;
                }
                Vertex& get_vertex = geometry.get_vertex(id.position);
                if (id.normal != -1) {
                    // Invalid normal id
                    if (id.normal > normals.size()) {
                        return std::nullopt;
                    }
                    get_vertex.normal = normals[id.normal];
                }

                vertex_ids.push_back(id.position);
            }

            // Add the connections.
            for (int i = 0; i < ids.size() - 1; i++) {
				geometry.add_connection(ids[i].position, ids[i + 1].position);
            }

            // Define the face
            geometry.define_face(vertex_ids);
        }
    }
    return geometry;
}