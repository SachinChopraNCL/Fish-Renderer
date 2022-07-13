add_library(asset asset_loader.cpp model_loader.cpp shader_loader.cpp texture_loader.cpp)
find_package(assimp REQUIRED)
target_link_libraries(asset stb glad assimp::assimp)
target_include_directories(asset PUBLIC 
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/asset/
						   ${CMAKE_SOURCE_DIR}/Fish-Renderer/include/
						  )
