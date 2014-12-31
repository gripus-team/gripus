cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(gripus)
# the version number
set (GRIPUS_VERSION 0100)

#configure_file("${PROJECT_SOURCE_DIR}/gripus_config.h.in" "${PROJECT_BINARY_DIR}/gripus_config.h")
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(dependencies)
add_subdirectory(gripus-core)
#add_subdirectory(gripus-simulator)
#add_subdirectory(gripus-viewer)
