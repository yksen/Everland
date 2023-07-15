cmake_minimum_required(VERSION 3.15...3.23)
project(Everland LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(lib)
add_subdirectory(src)

add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/src/Everland.exe
    DEPENDS Everland
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)