cmake_minimum_required(VERSION 3.22)
project("Raytracer")

# config
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenGL REQUIRED)

# ============== glfw ==============
find_package(glfw3)
# ==================================

add_subdirectory(vendor/imgui)

add_executable(raytrace
  src/main.cpp 
  src/window/window.cpp
  src/renderer/renderer.cpp
	src/core/timer.cpp
	src/scene/shpere.cpp
)

target_include_directories(raytrace PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

# deps
target_link_libraries(raytrace OpenGL::GL)
target_link_libraries(raytrace glfw)
target_link_libraries(raytrace imgui)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E create_symlink
		${CMAKE_BINARY_DIR}/compile_commands.json
		${CMAKE_SOURCE_DIR}/compile_commands.json
)