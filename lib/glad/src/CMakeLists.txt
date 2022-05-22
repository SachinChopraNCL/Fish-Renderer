add_library(glad PUBLIC glad.c)

target_include_directories(glad PRIVATE ${CMAKE_SOURCE_DIR}/lib/glad/include)
