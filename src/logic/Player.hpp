#pragma once

#include "raylib-cpp.hpp"

namespace rl = raylib;

class Player
{
public:
    Player();
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    void update();

private:
    friend class Game;

    rl::Camera3D camera;
};