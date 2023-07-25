#pragma once

#include "raylib-cpp.hpp"

namespace rl = raylib;

enum class GameMode : bool
{
    Survival,
    Creative
};

class Player
{
public:
    Player();
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

    void processInput();
    void update();
    void draw();

private:
    friend class Game;

    void creativeMovement();
    void survivalMovement();

    rl::Camera3D camera;
    CameraMode cameraMode{CAMERA_FIRST_PERSON};
    GameMode gameMode{GameMode::Creative};
};