cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SOURCE_DIR src)

set(HEADERS include/Engine.h
	include/InputManager.h
	include/EMath.h
	include/Light.h
	include/Scene.h
	include/Transform.h
	include/Renderer/Camera.h
	include/Renderer/Shader.h
	include/Renderer/Vertex.h
	include/Renderer/Triangle.h
	include/Renderer/TriangleRenderer.h
	include/Renderer/Mesh.h
	include/Renderer/Meshbuffer.h

	src/Renderer/Glerror.h
)
set(SOURCES ${PROJECT_SOURCE_DIR}/Engine.cc
	${PROJECT_SOURCE_DIR}/InputManager.cc
	${PROJECT_SOURCE_DIR}/Scene.cc
	${PROJECT_SOURCE_DIR}/Transform.cc
	${PROJECT_SOURCE_DIR}/Renderer/Camera.cc
	${PROJECT_SOURCE_DIR}/Renderer/Shader.cc
	${PROJECT_SOURCE_DIR}/Renderer/Vertex.cc
	${PROJECT_SOURCE_DIR}/Renderer/Triangle.cc
	${PROJECT_SOURCE_DIR}/Renderer/TriangleRenderer.cc
	${PROJECT_SOURCE_DIR}/Renderer/Mesh.cc
	${PROJECT_SOURCE_DIR}/Renderer/Meshbuffer.cc
	${PROJECT_SOURCE_DIR}/Renderer/Glerror.cc
)

add_subdirectory(external/GLFW)
add_subdirectory(external/glad)
add_subdirectory(external/GLM)


add_library(Engine STATIC
	${SOURCES} ${HEADERS}
)

target_include_directories(
	Engine PUBLIC include src
)

target_link_libraries(Engine PUBLIC glfw glad glm)

set_target_properties(Engine PROPERTIES LINKER_LANGUAGE CXX)