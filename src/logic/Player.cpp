#include "Player.hpp"

Player::Player()
{
    camera.position = {1.0f, 60.0f, 1.0f};
    camera.target = {2.0f, 1.0f, 1.0f};
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

    processMovement();
}

void Player::processMovement()
{
    const float dt = GetFrameTime();
    static constexpr float flightSpeedMultiplier{2.0f};
    float flightSpeed{8.0f};

    if (IsKeyDown(KEY_LEFT_CONTROL))
        flightSpeed *= flightSpeedMultiplier;

    if (IsKeyDown(KEY_SPACE))
    {
        camera.position.y += flightSpeed * dt;
        camera.target.y += flightSpeed * dt;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        camera.position.y -= flightSpeed * dt;
        camera.target.y -= flightSpeed * dt;
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
