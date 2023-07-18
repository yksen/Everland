#pragma once

#include "raylib-cpp.hpp"

#include <world/World.hpp>

#include <memory>

namespace rl = raylib;

class Game
{
public:
    Game(std::unique_ptr<World> &&world);
    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;
    ~Game() = default;

private:
    void processInput();
    void update();
    void draw();
    void gameLoop();

    std::unique_ptr<World> world;
    rl::Camera camera;
    Vector3 playerPosition{0.0f, 0.0f, 0.0f};
};