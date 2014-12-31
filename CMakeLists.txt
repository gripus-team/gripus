cmake_minimum_required(VERSION 2.6)

project(gripus)
# the version number
set (GRIPUS_VERSION 0x0100)

configure_file {
	"${PROJECT_SOURCE_DIR}/gripus_config.h.in"
	"${PROJECT_BINARY_DIR}/girpus_config.h"
}
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(gripus-core)
add_subdirectory(gripus-simulator)
add_subdirectory(gripus-viewer)