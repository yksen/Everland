#pragma once

#include <logic/Player.hpp>
#include <world/World.hpp>

#include <raylib-cpp.hpp>

#include <memory>

namespace rl = raylib;

struct GameOptions
{
    int renderDistance{6};
    bool debugModeEnabled{false};
};

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
    void drawDebugInfo();
    void gameLoop();

    std::unique_ptr<World> world;
    Player player;
    GameOptions options;
};