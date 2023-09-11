set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Application.cpp
    ${CMAKE_SOURCE_DIR}/src/logic/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/logic/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/world/World.cpp
    ${CMAKE_SOURCE_DIR}/src/world/Generator.cpp
    ${CMAKE_SOURCE_DIR}/src/world/MeshBuilder.cpp
)

add_library(EverlandLib STATIC ${SOURCES})
target_link_libraries(EverlandLib PUBLIC fmt raylib raylib_cpp)

target_include_directories(EverlandLib PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_include_directories(EverlandLib SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/lib/magic_enum/include
    ${CMAKE_SOURCE_DIR}/lib/raylib-cpp/include
    ${CMAKE_SOURCE_DIR}/lib/PerlinNoise
)

if (MSVC)
    target_compile_options(EverlandLib PUBLIC /W4)
else()
    target_compile_options(EverlandLib PUBLIC -Wall -Wextra -pedantic)
endif()

add_executable(Everland main.cpp ${SOURCES})
target_link_libraries(Everland PUBLIC EverlandLib)