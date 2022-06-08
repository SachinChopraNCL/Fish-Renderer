add_library(componentlib transformable.cpp)

find_package(glm REQUIRED)

target_link_libraries(componentlib glm::glm)

target_include_directories(componentlib    
                           PUBLIC 
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/render-component
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
                           )