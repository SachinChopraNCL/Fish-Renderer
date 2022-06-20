add_library("render-component" transformable.cpp)

find_package(glm REQUIRED)

target_link_libraries("render-component" glm::glm)

target_include_directories("render-component"    
                           PUBLIC 
                           "${CMAKE_SOURCE_DIR}/Fish-Renderer/include/render-component"
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
                           )