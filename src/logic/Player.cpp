#include "Player.hpp"

Player::Player()
{
    camera.position = {1.0f, 0.0f, 0.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 100.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Player::update()
{
    camera.Update(CAMERA_PERSPECTIVE);
}