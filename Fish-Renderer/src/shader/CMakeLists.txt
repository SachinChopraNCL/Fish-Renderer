add_library(shader shader.cpp)
target_link_libraries(shader glad asset)
target_include_directories(shader 
						   PUBLIC 
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/shader/
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
                           )