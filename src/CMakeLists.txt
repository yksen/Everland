add_compile_options(-Wall -Wextra -Wpedantic -Werror)

set(SOURCES
    Application.cpp
    main.cpp
)

add_executable(Everland ${SOURCES})

target_link_libraries(Everland PRIVATE raylib)
