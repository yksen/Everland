set(SOURCES
    main.cpp
    Application.cpp
    logic/Game.cpp
    logic/Player.cpp
    world/World.cpp
    world/Generator.cpp
)
add_executable(Everland ${SOURCES})

target_include_directories(Everland PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(Everland SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/include)

target_link_libraries(Everland PRIVATE raylib raylib_cpp)

if (MSVC)
    target_compile_options(Everland PRIVATE /W4)
else()
    target_compile_options(Everland PRIVATE -Wall -Wextra -pedantic)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})