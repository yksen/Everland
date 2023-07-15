#include "Game.hpp"
#include "raylib.h"

Game::Game(std::unique_ptr<World> &&world)
    : world{std::move(world)}
{
    SetExitKey(KEY_NULL);
}

void Game::processInput()
{
}

void Game::update()
{
}

void Game::draw()
{
    BeginDrawing();
    {
        ClearBackground(GREEN);
        DrawText(world->name.c_str(), 10, 10, 20, BLACK);
    }
    EndDrawing();
}

void Game::gameLoop()
{
    while (!IsKeyPressed(KEY_ESCAPE))
    {
        processInput();
        update();
        draw();
    }
    SetExitKey(KEY_ESCAPE);
}