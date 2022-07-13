cmake_minimum_required (VERSION 3.8)



# Add source to this project's executable.
add_executable (Fish-Renderer Fish-Renderer.cpp "asset/asset_loader.cpp")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set(CMAKE_CXX_STANDARD 20)
  set_property(TARGET Fish-Renderer PROPERTY CXX_STANDARD 20)
endif()


set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/GLFW")
set(glm_DIR "C:/Program Files (x86)/glm/lib/cmake/glm")

# Add glad 
add_library(glad ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/lib/glad/include)

# Add stb_image 
add_library(stb ${CMAKE_SOURCE_DIR}/lib/stb_image/src/stb_image.cpp)
target_include_directories(stb PUBLIC ${CMAKE_SOURCE_DIR}/lib/stb_image/include)



add_subdirectory("render-component")
add_subdirectory(asset)
add_subdirectory(shader)
add_subdirectory(buffer)
add_subdirectory(renderer)
add_subdirectory(camera)

target_link_libraries(Fish-Renderer PUBLIC renderer)

include_directories(${CMAKE_SOURCE_DIR}/Fish-Renderer/include)


