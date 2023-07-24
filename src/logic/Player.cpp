#include "Player.hpp"

Player::Player()
{
    camera.position = {1.0f, 1.0f, 1.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 100.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Player::processInput()
{
    if (IsKeyPressed(KEY_R))
    {
        cameraMode = (cameraMode == CAMERA_FIRST_PERSON) ? CAMERA_THIRD_PERSON : CAMERA_FIRST_PERSON;
        camera.up = {0.0f, 1.0f, 0.0f};
    }
}

void Player::update()
{
    camera.Update(cameraMode);
}

void Player::draw()
{
    if (cameraMode == CAMERA_THIRD_PERSON)
    {
        DrawCube(camera.target, 0.5f, 0.5f, 0.5f, GRAY);
        DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, BLACK);
    }
}