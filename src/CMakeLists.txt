set(SOURCES
    Application.cpp
    Game.cpp
    main.cpp
)

add_executable(Everland ${SOURCES})

target_link_libraries(Everland PRIVATE raylib)

if (MSVC)
    target_compile_options(Everland PRIVATE /W4)
else()
    target_compile_options(Everland PRIVATE -Wall -Wextra -pedantic)
endif()