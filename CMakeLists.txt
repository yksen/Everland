cmake_minimum_required(VERSION 3.15...3.27)
project(Everland LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/logic/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/logic/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/world/World.cpp
    ${CMAKE_SOURCE_DIR}/src/world/Generator.cpp
    ${CMAKE_SOURCE_DIR}/src/world/MeshBuilder.cpp
)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/src/Everland.exe
    DEPENDS Everland
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

enable_testing()