#pragma once

#include "raylib-cpp.hpp"

#include <logic/Game.hpp>
#include <world/World.hpp>

#include <memory>
#include <vector>

namespace rl = raylib;

struct ApplicationOptions
{
    bool debugModeEnabled{false};
};

class Application
{
public:
    Application(const ApplicationOptions &options);
    Application(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &) = delete;
    Application &operator=(Application &&) = delete;
    ~Application() = default;

private:
    void processInput();
    void update();
    void draw();
    void drawMenu();
    void appLoop();

    rl::Window window;
    ApplicationOptions options;
    std::unique_ptr<Game> game;
    std::vector<std::unique_ptr<World>> worlds;
};
