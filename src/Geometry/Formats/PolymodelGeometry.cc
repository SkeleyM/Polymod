#include <Geometry/Formats/PolymodelGeometry.h>

#define FILE_VERSION_MAJOR 0
#define FILE_VERSION_MINOR 0

std::vector<uint8_t> GeometryFormat::PolymodelGeometry::GeometryHeader::to_bytes() {
	std::vector<uint8_t> bytes;

	for (auto& byte : this->name)
		bytes.push_back(byte);
	// Null terminator
	bytes.push_back('\0');

	uint8_t* size_bytes = (uint8_t *)& this->data_size_prefix;
	for (int i = 0; i < sizeof(uint32_t); i++)
		bytes.push_back(*(size_bytes + i));

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

template <typename TableType>
std::vector<uint8_t> GeometryFormat::PolymodelGeometry::Table<TableType>::to_bytes() {
	std::vector<uint8_t> bytes;
	auto header_bytes = this->header.to_bytes();
	bytes.insert(bytes.back(), header_bytes);

	std::vector<uint8_t> data_bytes;

	for (auto& data : this->data) {
		auto& data = this->data[0];

		// Push bytes
		for (int b = 0; b < sizeof(TableType); b++) {
			data_bytes.push_back(*(&data + b));
			bytes.insert(bytes.back(), data_bytes);
		}
	}

	return bytes;
}

std::string GeometryFormat::PolymodelGeometry::serialize(Geometry geometry) {
	FileHeader header(FILE_VERSION_MAJOR, FILE_VERSION_MINOR);
	GeometryHeader geometry_header;
	geometry_header.name = geometry.name;



	return "";
}

std::optional<Geometry> GeometryFormat::PolymodelGeometry::deserialize(std::string source) {
	return std::nullopt;
}