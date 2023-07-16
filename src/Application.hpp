#pragma once

#include "Game.hpp"
#include "world/World.hpp"

#include <memory>
#include <vector>

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
    void appLoop();

    ApplicationOptions options;
    std::unique_ptr<Game> game;
    std::vector<std::unique_ptr<World>> worlds;
};
