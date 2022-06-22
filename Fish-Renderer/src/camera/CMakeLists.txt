add_library(camera camera.cpp)

find_package(glm REQUIRED)

target_link_libraries(camera glm::glm)

target_include_directories(camera 
						   PUBLIC 
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/camera 
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
						  )


