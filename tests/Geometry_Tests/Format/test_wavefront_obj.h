#pragma once

#include <Common/test_log.h>

#include <Geometry/Geometry.h>
#include <Geometry/Formats/GeometryFormats.h>

std::optional<Geometry> import_wavefront(std::string path) {
	GeometryFormat::GeometryFormatSpec spec;
	spec.geometry_format = GeometryFormat::GeometryFormatType::WavefrontObj;
	auto factory = GeometryFormat::GeometryFormatFactory();
	auto format = factory.create_format(spec);

	return GeometryFormat::GeometryFileHandler::import_geometry(format.get(), path);
}

void import_invalid_path() {
	// Obviously dont create this file its to test the failure
	ASSERT_FALSE(import_wavefront("./DoesNotExist.obj").has_value());
}

void test_wavefront_obj() {
	import_invalid_path();
}