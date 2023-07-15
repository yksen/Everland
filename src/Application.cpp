#include "Application.hpp"
#include "raylib.h"

Application::Application(const ApplicationOptions &options)
    : options(options)
{
    InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), "Everland");
    SetTargetFPS(144);

    appLoop();
}

void Application::processInput()
{
    if (IsKeyPressed(KEY_N))
        game = std::make_unique<Game>(std::make_unique<World>("New World"));
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