set(SOURCES
    Application.cpp
    Camera.cpp
    Player.cpp
    Window.cpp
    World.cpp
    main.cpp
)

set(INCLUDES
    ${CMAKE_SOURCE_DIR}/lib/glfw/include
)

include_directories(${INCLUDES})

add_executable(Everland ${SOURCES})

target_link_libraries(Everland PRIVATE gdi32 glad glfw glm)
