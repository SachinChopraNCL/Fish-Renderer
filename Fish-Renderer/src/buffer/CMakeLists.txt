add_library(buffer vertex_array.cpp )
target_link_libraries(buffer glad)
target_include_directories(buffer 
						   PUBLIC 
                           ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/buffer/
						  )