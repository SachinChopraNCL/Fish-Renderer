add_library(renderer render_object.cpp)
target_link_libraries(renderer glad)
target_include_directories(renderer    
                           PUBLIC 
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/renderer/
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/buffer/
                           )