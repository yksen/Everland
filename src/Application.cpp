#include "Application.hpp"
#include "raylib-cpp.hpp"

Application::Application(const ApplicationOptions &options) : options{options}
{
    window.Init(GetScreenWidth(), GetScreenHeight(), "Everland");
    window.SetTargetFPS(144);

    worlds = World::discoverLocalWorlds();
    appLoop();
}

void Application::processInput()
{
    if (IsKeyPressed(KEY_N))
        game = std::make_unique<Game>(std::make_unique<World>("New World", std::make_unique<DefaultGenerator>()));
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
        window.DrawFPS(10, 10);
        drawMenu();
    }
    EndDrawing();
}

void Application::drawMenu()
{
    DrawText("Everland", centerTextHorizontally("Everland", 100), 50, 100, WHITE);
    for (uint32_t i = 0; i < worlds.size(); ++i)
        DrawText(worlds[i]->name.c_str(), centerTextHorizontally(worlds[i]->name, 50), 200 + 100 * i, 50, WHITE);
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