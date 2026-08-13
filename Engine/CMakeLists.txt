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

	include/imgui_impl/ImGui.h
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

	${PROJECT_SOURCE_DIR}/imgui_impl/ImGui.cc
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${HEADERS} ${SOURCES}
)

add_subdirectory(external/GLFW)
add_subdirectory(external/glad)
add_subdirectory(external/GLM)

# Build IMGUI here
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(imgui_HEADERS 
	external/imgui/imgui.h
	external/imgui/imconfig.h
	external/imgui/imgui_internal.h
	external/imgui/imstb_rectpack.h
	external/imgui/imstb_textedit.h
	external/imgui/imstb_truetype.h

	external/imgui/backends/imgui_impl_opengl3.h
	external/imgui/backends/imgui_impl_glfw.h
)
set(imgui_SOURCES 
	external/imgui/imgui.cpp
	external/imgui/imgui_tables.cpp
	external/imgui/imgui_widgets.cpp
	external/imgui/imgui_draw.cpp
	external/imgui/imgui_demo.cpp

	external/imgui/backends/imgui_impl_opengl3.cpp
	external/imgui/backends/imgui_impl_glfw.cpp	
)

add_library(imgui STATIC
	${imgui_SOURCES} ${imgui_HEADERS}
)

target_include_directories(
	imgui PUBLIC external/imgui/
	external/glfw/include
)

# Finish building library

add_library(Engine STATIC
	${SOURCES} ${HEADERS}
)

target_include_directories(
	Engine PUBLIC include src
)

target_link_libraries(Engine PUBLIC glfw glad glm imgui)

set_target_properties(Engine PROPERTIES LINKER_LANGUAGE CXX)