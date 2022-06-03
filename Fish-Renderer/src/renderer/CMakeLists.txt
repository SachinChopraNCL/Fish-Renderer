add_library(renderer renderer.cpp render_object.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)


target_link_libraries(renderer PUBLIC shader buffer glfw glad glm::glm)

target_include_directories(renderer    
                           PUBLIC 
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/renderer/
                           )