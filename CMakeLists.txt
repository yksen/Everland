cmake_minimum_required(VERSION 3.15...3.23)
project(Everland LANGUAGES CXX)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(lib)
add_subdirectory(src)