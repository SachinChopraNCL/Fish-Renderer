cmake_minimum_required (VERSION 3.8)



# Add source to this project's executable.
add_executable (Fish-Renderer "Fish-Renderer.cpp")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Fish-Renderer PROPERTY CXX_STANDARD 20)
endif()


set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/GLFW")
set(glm_DIR "C:/Program Files (x86)/glm/lib/cmake/glm")

add_subdirectory(shader)
add_subdirectory(buffer)
add_subdirectory(renderer)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Add glad 
add_library(glad ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/lib/glad/include)


target_link_libraries(Fish-Renderer PUBLIC shader buffer glfw glad glm::glm)

include_directories(${CMAKE_SOURCE_DIR}/Fish-Renderer/include)


