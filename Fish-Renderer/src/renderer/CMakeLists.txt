add_library(renderer renderer.cpp render_object.cpp mesh.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(renderer PUBLIC "render-component" camera asset shader buffer glfw glad)

target_include_directories(renderer    
                           PUBLIC 
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/renderer/
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
                           )