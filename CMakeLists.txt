cmake_minimum_required(VERSION 2.8)

project(gripus)
set (GRIPUS_VERSION 0100)

# configure_file("${PROJECT_SOURCE_DIR}/gripus_config.h.in" "${PROJECT_BINARY_DIR}/gripus_config.h")
# include_directories("${PROJECT_BINARY_DIR}")

# dependencies
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_subdirectory(dependencies)
include_directories("dependencies/glm")
include_directories("dependencies/tinyxml")
include_directories("dependencies/glfw/include")
include_directories("dependencies/assimp/include")

# gripus-core, as the main library of the project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g3")
add_subdirectory(gripus-core)

# gripus-simulator and gripus-viewer both use gripus-core together with other libraries
include_directories(gripus-core)
add_subdirectory(gripus-simulator)
add_subdirectory(gripus-viewer)
