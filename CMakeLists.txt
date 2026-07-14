cmake_minimum_required(VERSION 3.10)
project(3Dmodelling)

set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SOURCE_DIR src)

add_subdirectory(Engine)

add_executable(3Dmodelling)

target_link_libraries(3Dmodelling
	PUBLIC
	Engine
)

target_sources(3Dmodelling
	PRIVATE
	${PROJECT_SOURCE_DIR}/main.cc
)