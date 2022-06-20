add_library(shader shader.cpp)
find_package(glm REQUIRED)
target_link_libraries(shader glm::glm glad asset)
target_include_directories(shader 
						   PUBLIC 
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/shader/
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
                           )