cmake_minimum_required(VERSION 3.0)

project(app)

add_definitions(-Os)

add_subdirectory("./lib")

file(GLOB sourceFiles ./syntax_highlight.c)

add_executable(syntax_highlight ${sourceFiles})

target_link_libraries(syntax_highlight cpp_lib)