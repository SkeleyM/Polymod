project(ReferenceImages)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES ReferenceImage.h
	ReferenceImageManager.h
	ReferenceImageManager.cc
)

add_library(ReferenceImages ${SOURCES})

target_link_libraries(ReferenceImages Engine )
target_include_directories(ReferenceImages PUBLIC .)