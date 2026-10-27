cmake_minimum_required(VERSION 3.10)
project(DirectoryResolver)

set(CMAKE_CXX_STANDARD 17)
set(SOURCES 
	DirectoryResolverFactory.cc
)

set(HEADERS
	Common/AbstractDirectoryResolver.h
	Common/DirectoryTypes.h
	LinuxResolver/LinuxResolver.h
	MacResolver/MacResolver.h
	WindowsResolver/WindowsResolver.h

	DirectoryResolver.h
	DirectoryResolverFactory.h
)

add_library(DirectoryResolver STATIC DirectoryResolver.h)
target_sources(DirectoryResolver PRIVATE ${HEADERS} ${SOURCES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
    FILES ${HEADERS} ${SOURCES} 
)

set_target_properties(DirectoryResolver PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
	DirectoryResolver PUBLIC ./ .
)
