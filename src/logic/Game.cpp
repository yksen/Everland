#include "Game.hpp"
#include "raylib-cpp.hpp"

Game::Game(std::unique_ptr<World> &&world) : world{std::move(world)}
{
    SetExitKey(KEY_NULL);
    DisableCursor();

    camera.position = Vector3{0.0f, 10.0f, 0.0f};
    camera.target = Vector3{0.0f, 0.0f, 0.0f};
    camera.up = Vector3{0.0f, 0.0f, 1.0f};
    camera.fovy = 100.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    gameLoop();
}

void Game::processInput()
{
}

void Game::update()
{
}

void Game::draw()
{
    UpdateCamera(&camera, CAMERA_PERSPECTIVE);
    BeginDrawing();
    {
        ClearBackground(BLUE);
        BeginMode3D(camera);
        {
            world->draw(playerPosition, Vector3{0.0f, 0.0f, 0.0f}, 1);
        }
        EndMode3D();
        DrawText(world->name.c_str(), 10, 30, 20, BLACK);
        DrawFPS(10, 10);
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
    world.reset();
    SetExitKey(KEY_ESCAPE);
}