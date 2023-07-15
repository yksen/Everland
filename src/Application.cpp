#include "Application.hpp"
#include "raylib.h"

Application::Application(const ApplicationOptions &options)
    : options(options)
{
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Everland");
    SetTargetFPS(60);

    gameLoop();
}

void Application::gameLoop()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}