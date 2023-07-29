cmake_minimum_required(VERSION 3.15...3.27)
project(Everland LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/src/Everland.exe
    DEPENDS Everland
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)