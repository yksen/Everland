#include "Game.hpp"
#include "raylib-cpp.hpp"

#include <fmt/core.h>

Game::Game(std::unique_ptr<World> &&world) : world{std::move(world)}
{
    SetExitKey(KEY_NULL);
    DisableCursor();
    gameLoop();
}

void Game::processInput()
{
    if (IsKeyPressed(KEY_F3))
        options.debugModeEnabled = !options.debugModeEnabled;

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
            world->draw(player.camera.target, options.debugModeEnabled);
            player.draw();
        }
        EndMode3D();

        if (options.debugModeEnabled)
            drawDebugInfo();
    }
    EndDrawing();
}

void Game::drawDebugInfo()
{
    static constexpr Color fontColor = BLACK;
    static constexpr int fontSize = 20;
    static constexpr int leftMargin = 20;
    static constexpr int rowSpacing = 20;
    int rowNumber = 0;

    const auto &camera = player.camera;

    std::string cameraPosition =
        fmt::format("{:.3f}\t{:.3f}\t{:.3f}", camera.position.x, camera.position.y, camera.position.z);
    std::string cameraTarget = fmt::format("{:.3f}\t{:.3f}\t{:.3f}", camera.target.x, camera.target.y, camera.target.z);

    DrawFPS(leftMargin, rowSpacing * ++rowNumber);
    DrawText(world->name.c_str(), leftMargin, rowSpacing * ++rowNumber, fontSize, fontColor);
    DrawText(cameraPosition.c_str(), leftMargin, rowSpacing * ++rowNumber, fontSize, fontColor);
    DrawText(cameraTarget.c_str(), leftMargin, rowSpacing * ++rowNumber, fontSize, fontColor);
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