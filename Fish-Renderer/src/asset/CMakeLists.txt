add_library(asset asset_loader.cpp shader_loader.cpp texture_loader.cpp)

target_link_libraries(asset stb glad)
target_include_directories(asset PUBLIC 
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/asset/
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
						  )
