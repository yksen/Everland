#include "Application.hpp"
#include "raylib.h"

Application::Application(const ApplicationOptions &options)
    : options(options)
{
    InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "Everland");
    SetTargetFPS(144);

    game = std::make_unique<Game>();
    appLoop();
}

void Application::processInput()
{
}

void Application::update()
{
}

void Application::draw()
{
    BeginDrawing();
    {
        ClearBackground(BLACK);
    }
    EndDrawing();
}

void Application::appLoop()
{
    while (!WindowShouldClose())
    {
        if (game)
        {
            game->gameLoop();
            game.release();
            SetExitKey(KEY_ESCAPE);
        }
        else
        {
            processInput();
            update();
            draw();
        }
    }
    CloseWindow();
}