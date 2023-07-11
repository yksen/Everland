set(SOURCES
    Application.cpp
    Camera.cpp
    Player.cpp
    Window.cpp
    World.cpp
    main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Everland ${SOURCES})

target_link_libraries(Everland PRIVATE gdi32 glad glfw glm)
