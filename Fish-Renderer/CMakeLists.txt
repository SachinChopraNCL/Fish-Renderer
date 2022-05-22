cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Fish-Renderer "Fish-Renderer.cpp" "Fish-Renderer.h")



set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/GLFW")
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Add glad 
add_library(glad ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/lib/glad/include)


target_link_libraries(Fish-Renderer PUBLIC glfw glad)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Fish-Renderer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
