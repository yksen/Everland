set(TEST_SOURCES
    world/WorldTest.cpp
)

add_executable(EverlandTest ${TEST_SOURCES})
target_link_libraries(EverlandTest gtest gtest_main EverlandLib)

include(GoogleTest)
gtest_discover_tests(EverlandTest
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)