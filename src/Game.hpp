#pragma once

#include "raylib.h"

class Game
{
public:
    Game();
    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;
    ~Game() = default;

    void processInput();
    void update();
    void draw();
    void gameLoop();

private:
};