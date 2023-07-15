#include "Application.hpp"
#include "raylib.h"

Application::Application(bool debugModeEnabled) : debugModeEnabled(debugModeEnabled)
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