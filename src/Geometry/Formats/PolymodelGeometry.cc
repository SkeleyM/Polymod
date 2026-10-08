#include <Geometry/Formats/PolymodelGeometry.h>

#include <cstring>
#include <iostream>

#define FILE_VERSION_MAJOR 0
#define FILE_VERSION_MINOR 0

// Geometry Header impl
std::unique_ptr<uint8_t[]> GeometryFormat::PolymodelGeometry::GeometryHeader::to_bytes(size_t* table_size_bytes) {
	// +1 for null terminator
	size_t buffer_size = this->name.size() + 1 + sizeof(this->data_size_prefix); 

	std::cout << "Gheader_size " <<	buffer_size << std::endl;

	//CRASHES HERE
	auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[buffer_size]);
	std::cout << "post " <<	buffer_size << std::endl;

	std::memcpy(bytes.get(), this->name.c_str(), this->name.size() + 1);
	std::memcpy(bytes.get() + this->name.size() + 1, &this->data_size_prefix, sizeof(this->data_size_prefix));

	*table_size_bytes = buffer_size;

	return bytes;
};

GeometryFormat::PolymodelGeometry::GeometryHeader GeometryFormat::PolymodelGeometry::GeometryHeader::from_bytes(uint8_t* bytes, size_t& bytes_read) {
	GeometryFormat::PolymodelGeometry::GeometryHeader header;
	
	size_t index = 0;
	while (bytes[index] != '\0')
		header.name.push_back(bytes[index++]);
	// Skip over null terminator
	index++;

	std::memcpy(&header.data_size_prefix, bytes + index, sizeof(header.data_size_prefix));

	return header;
};

// Table Header impl
std::unique_ptr<uint8_t[]> GeometryFormat::PolymodelGeometry::TableHeader::to_bytes(size_t* table_size_bytes) {
	// +1 for null terminator
	size_t buffer_size = this->name.size() + 1 + 2*(sizeof(uint32_t));

	std::cout << "Tbh_size " << buffer_size << std::endl;
	auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[buffer_size]);

	std::memcpy(bytes.get(), this->name.c_str(), this->name.size() + 1);
	std::memcpy(bytes.get() + this->name.size() + 1, &this->table_element_count, 2 * sizeof(uint32_t));

	*table_size_bytes = buffer_size;

	return bytes;
};


GeometryFormat::PolymodelGeometry::TableHeader GeometryFormat::PolymodelGeometry::TableHeader::from_bytes(uint8_t* bytes, size_t& bytes_read) {
	abort();
	return {};
};

// Table impl
template <typename TableType>
std::unique_ptr<uint8_t[]> GeometryFormat::PolymodelGeometry::Table<TableType>::to_bytes(size_t* table_size) {
	// Configure header
	this->header.table_size_prefix = this->data.size() * sizeof(TableType);
	this->header.table_element_count = this->data.size();
	size_t header_bytes_size;
	auto header_bytes = this->header.to_bytes(&header_bytes_size);

	size_t buffer_size = sizeof(TableType) * this->data.size() + header_bytes_size;

	std::cout << "Tble_size " << buffer_size << std::endl;
	auto bytes = std::unique_ptr<uint8_t[]>(new uint8_t[buffer_size]);

	// Copy header bytes
	std::memcpy(bytes.get(), header_bytes.get(), header_bytes_size);

	// Copy data bytes
	std::memcpy(bytes.get() + header_bytes_size, this->data.data(), this->data.size() * sizeof(TableType));

	return bytes;
}

template <typename TableType>
GeometryFormat::PolymodelGeometry::Table<TableType> GeometryFormat::PolymodelGeometry::Table<TableType>::from_bytes(uint8_t* bytes, size_t& bytes_read) {
	abort();
	return {};
}


std::string GeometryFormat::PolymodelGeometry::serialize(Geometry geometry) {
	FileHeader header(FILE_VERSION_MAJOR, FILE_VERSION_MINOR);
	GeometryHeader geometry_header;
	geometry_header.name = geometry.name;

	Table<Vector3> position_table("VertexPositionTable");
	Table<Vector3> normal_table("VertexNormalTable");

	for (auto& id : geometry.get_all_vertex_ids()) {
		Vertex& vertex = geometry.get_vertex(id);
		position_table.data.push_back(vertex.position);
		normal_table.data.push_back(vertex.normal);
	}

	size_t position_bytes_size;
	auto position_bytes = position_table.to_bytes(&position_bytes_size);
	size_t normal_bytes_size;
	auto normal_bytes = normal_table.to_bytes(&normal_bytes_size);


	std::vector<uint8_t> bytes;

	// Write data to the buffer;
	size_t header_size_bytes;
	auto header_bytes = geometry_header.to_bytes(&header_size_bytes);

	bytes.insert(bytes.end(), (uint8_t*)&header, (uint8_t*)(&header + sizeof(FileHeader)));
	bytes.insert(bytes.end(), header_bytes.get(), header_bytes.get() + header_size_bytes);
	bytes.insert(bytes.end(), position_bytes.get(), position_bytes.get() + position_bytes_size);
	bytes.insert(bytes.end(), normal_bytes.get(), normal_bytes.get() + normal_bytes_size);


	return std::string(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

std::optional<Geometry> GeometryFormat::PolymodelGeometry::deserialize(std::string source) {
	return std::nullopt;
}