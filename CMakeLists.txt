cmake_minimum_required(VERSION 3.15...3.27)
project(Everland LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

enable_testing()

include(AddGoogleTest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(${CMAKE_SOURCE_DIR}/resources/shaders/fragment.glsl ${CMAKE_BINARY_DIR}/resources/shaders/fragment.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/resources/shaders/vertex.glsl ${CMAKE_BINARY_DIR}/resources/shaders/vertex.glsl COPYONLY)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

add_custom_target(run
    COMMAND Everland
    DEPENDS Everland
)
add_custom_target(run_tests
    COMMAND EverlandTest
    DEPENDS EverlandTest
)