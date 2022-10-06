cmake_minimum_required(VERSION 3.16)
project(example)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
include(libigl)

# Enable the target igl::glfw
igl_include(glfw)
igl_include(imgui)


set(
        main_src
        main.cpp
)

# Add your project files
add_executable(${PROJECT_NAME} ${main_src})
target_link_libraries(${PROJECT_NAME} PUBLIC igl::glfw igl::imgui)
