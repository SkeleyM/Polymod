#pragma once

#include <Geometry/Formats/AbstractGeometryFormat.h>

#include <string>
#include <vector>

namespace GeometryFormat {
	class PolymodelGeometry : AbstractGeometryFormat {
	public:
		class FileHeader {
		public:
			uint16_t version_major;
			uint16_t version_minor;
			FileHeader(uint16_t version_major, uint16_t version_minor) : version_major(version_major), version_minor(version_minor) {}
		};

		class GeometryHeader {
		public:
			std::string name;
			uint32_t data_size_prefix;

			std::vector<uint8_t> to_bytes();
			static GeometryHeader from_bytes(uint8_t* bytes, size_t& bytes_read);
		};

		class TableHeader {
		public:
			std::string name;
			uint32_t table_element_count;
			uint32_t table_size_prefix;
			std::vector<uint8_t> to_bytes();
			static TableHeader from_bytes(uint8_t* bytes, size_t& bytes_read);
		};

		template <typename TableType>
		class Table {
		public:
			TableHeader header;
			std::vector<TableType> data;

			std::vector<uint8_t> to_bytes();
			static Table<TableType> read_table(uint8_t* bytes, size_t& bytes_read);
		};

	public:
		PolymodelGeometry(GeometryFormatSpec spec) {
			this->spec = spec;
		}

		std::string serialize(Geometry geometry);
		std::optional<Geometry> deserialize(std::string source);
	};
}