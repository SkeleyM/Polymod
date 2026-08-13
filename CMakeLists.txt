cmake_minimum_required(VERSION 3.10)
project(3Dmodelling)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SOURCE_DIR src)

set(SOURCES
	${PROJECT_SOURCE_DIR}/OrbitalCameraController.cc
	${PROJECT_SOURCE_DIR}/GeometryManager.cc
	${PROJECT_SOURCE_DIR}/GeometryEditor.cc
	${PROJECT_SOURCE_DIR}/Geometry/Face.cc
	${PROJECT_SOURCE_DIR}/Geometry/Geometry.cc
	${PROJECT_SOURCE_DIR}/Geometry/Timeline.cc

	${PROJECT_SOURCE_DIR}/Geometry/Operations/AbstractGeometryOperation.cc
	${PROJECT_SOURCE_DIR}/Geometry/Operations/ExtrudeOperation.cc
	${PROJECT_SOURCE_DIR}/Geometry/Operations/MoveOperation.cc
	${PROJECT_SOURCE_DIR}/Geometry/Operations/RotateOperation.cc
	${PROJECT_SOURCE_DIR}/Geometry/Operations/ScaleOperation.cc
	${PROJECT_SOURCE_DIR}/Geometry/Operations/VertexSpinOperation.cc

	${PROJECT_SOURCE_DIR}/Ui/MenuBar.cc
	${PROJECT_SOURCE_DIR}/Ui/MenuBarItem.cc
	${PROJECT_SOURCE_DIR}/Ui/Toolbar.cc
)

set(HEADERS 
	${PROJECT_SOURCE_DIR}/OrbitalCameraController.h
	${PROJECT_SOURCE_DIR}/GeometryManager.h
	${PROJECT_SOURCE_DIR}/GeometryEditor.h
	${PROJECT_SOURCE_DIR}/Geometry/Face.h
	${PROJECT_SOURCE_DIR}/Geometry/Geometry.h
	${PROJECT_SOURCE_DIR}/Geometry/GeometryShadingType.h
	${PROJECT_SOURCE_DIR}/Geometry/Timeline.h

	${PROJECT_SOURCE_DIR}/Geometry/Operations/AbstractGeometryOperation.h
	${PROJECT_SOURCE_DIR}/Geometry/Operations/ExtrudeOperation.h
	${PROJECT_SOURCE_DIR}/Geometry/Operations/MoveOperation.h
	${PROJECT_SOURCE_DIR}/Geometry/Operations/RotateOperation.h
	${PROJECT_SOURCE_DIR}/Geometry/Operations/ScaleOperation.h
	${PROJECT_SOURCE_DIR}/Geometry/Operations/VertexSpinOperation.h

	${PROJECT_SOURCE_DIR}/Ui/MenuBar.h
	${PROJECT_SOURCE_DIR}/Ui/MenuBarItem.h
	${PROJECT_SOURCE_DIR}/Ui/Toolbar.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${HEADERS} ${SOURCES}
)

add_subdirectory(Engine)

add_executable(3Dmodelling)


if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/ZI>)

    # Enable Incremental Linking (/INCREMENTAL) required by Hot Reload
    target_link_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:/INCREMENTAL>)
endif()

target_link_libraries(3Dmodelling
	PUBLIC
	Engine
)

target_include_directories(3Dmodelling
	PUBLIC 	${PROJECT_SOURCE_DIR}/
)

target_sources(3Dmodelling
	PRIVATE
	${PROJECT_SOURCE_DIR}/main.cc
	${SOURCES}
	${HEADERS}
)