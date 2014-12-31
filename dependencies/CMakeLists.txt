cmake_minimum_required(VERSION 2.8)

# these are the dependencies
add_subdirectory(glfw)
add_subdirectory(tinyxml)
add_subdirectory(glm)

# 
include_directories(. "glm" "tinyxml" "glfw/include")
