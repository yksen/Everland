include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
include(GoogleTest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_SOURCES
    world/WorldTest.cpp
)
add_executable(EverlandTest
    ${SOURCES}
    ${TEST_SOURCES}
)

target_include_directories(EverlandTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(EverlandTest SYSTEM PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/magic_enum/include
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/include
    ${CMAKE_SOURCE_DIR}/lib/PerlinNoise
)

target_link_libraries(EverlandTest gtest_main fmt raylib raylib_cpp)

gtest_discover_tests(EverlandTest)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS EverlandTest Everland
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)