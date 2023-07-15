#include "Game.hpp"

Game::Game()
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
}