cmake_minimum_required(VERSION 3.10)
project(3Dmodelling)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SOURCE_DIR src)

set(SOURCES
	${PROJECT_SOURCE_DIR}/OrbitalCameraController.cc
	${PROJECT_SOURCE_DIR}/Geometry/Geometry.cc
	${PROJECT_SOURCE_DIR}/Geometry/Face.cc
)

set(HEADERS 
	${PROJECT_SOURCE_DIR}/OrbitalCameraController.h
	${PROJECT_SOURCE_DIR}/Geometry/Geometry.h
	${PROJECT_SOURCE_DIR}/Geometry/Face.h
)

add_subdirectory(Engine)

add_executable(3Dmodelling)

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