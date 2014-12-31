project(gripus-viewer)

file(GLOB SOURCES *.cpp)
add_executable(gripus-viewer ${SOURCES})
target_link_libraries(gripus-viewer gripus-core ${OPENGL_LIBRARIES} Xxf86vm Xrandr Xi Xext glfw pthread ${X11_LIBRARIES})
