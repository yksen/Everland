#include "Game.hpp"
#include "raylib-cpp.hpp"

Game::Game(std::unique_ptr<World> &&world) : world{std::move(world)}
{
    SetExitKey(KEY_NULL);
    DisableCursor();
    gameLoop();
}

void Game::processInput()
{
    player.processInput();
}

void Game::update()
{
    world->update(player.camera.position, options.renderDistance);
    player.update();
}

void Game::draw()
{
    BeginDrawing();
    {
        ClearBackground(BLUE);
        BeginMode3D(player.camera);
        {
            world->draw(player.camera.target, options.renderDistance);
            player.draw();
        }
        EndMode3D();
        DrawText(world->name.c_str(), 10, 30, 20, BLACK);
        std::string cameraPosition = std::to_string(player.camera.position.x) + "\t" +
                                     std::to_string(player.camera.position.y) + "\t" +
                                     std::to_string(player.camera.position.z);
        std::string cameraTarget = std::to_string(player.camera.target.x) + "\t" +
                                   std::to_string(player.camera.target.y) + "\t" +
                                   std::to_string(player.camera.target.z);
        DrawText(cameraPosition.c_str(), 10, 50, 20, BLACK);
        DrawText(cameraTarget.c_str(), 10, 70, 20, BLACK);
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