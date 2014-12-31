cmake_minimum_required(VERSION 2.8)

project(gripus-core)

file(GLOB SOURCES *.cpp)
add_library(gripus-core ${SOURCES})
target_link_libraries(gripus-core tinyxml glm glfw)
