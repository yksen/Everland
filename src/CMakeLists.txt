set(SOURCES
    Application.cpp
    Game.cpp
    world/World.cpp
    world/Generator.cpp
    main.cpp
)

add_executable(Everland ${SOURCES})

target_link_libraries(Everland PRIVATE raylib)

if (MSVC)
    target_compile_options(Everland PRIVATE /W4)
else()
    target_compile_options(Everland PRIVATE -Wall -Wextra -pedantic)
endif()

target_include_directories(Everland PRIVATE ${CMAKE_SOURCE_DIR}/src)