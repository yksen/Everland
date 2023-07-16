#include "Application.hpp"
#include "raylib.h"

Application::Application(const ApplicationOptions &options)
    : options(options)
{
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Everland");
    SetTargetFPS(144);

    worlds = discoverLocalWorlds();
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

int centerTextHorizontally(const std::string &text, int fontSize, int width = GetScreenWidth())
{
    return width / 2 - MeasureText(text.c_str(), fontSize) / 2;
}

void Application::draw()
{
    BeginDrawing();
    {
        ClearBackground(BLACK);
        DrawFPS(10, 10);
        DrawText("Everland", centerTextHorizontally("Everland", 100), 50, 100, WHITE);
        for (uint32_t i = 0; i < worlds.size(); ++i)
            DrawText(worlds[i]->name.c_str(), centerTextHorizontally(worlds[i]->name, 50), 200 + 100 * i, 50, WHITE);
    }
    EndDrawing();
}

void Application::appLoop()
{
    while (!WindowShouldClose())
    {
        processInput();
        update();
        draw();
    }
    CloseWindow();
}