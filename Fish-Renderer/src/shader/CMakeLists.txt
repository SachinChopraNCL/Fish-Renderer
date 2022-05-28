add_library(shader shader.cpp shader_loader.cpp)
target_link_libraries(shader glad)
target_include_directories(shader 
						   PUBLIC 
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/shader/
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
                           )