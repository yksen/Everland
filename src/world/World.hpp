#pragma once

#include "raylib-cpp.hpp"

#include "Generator.hpp"

#include <chrono>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;
namespace rl = raylib;

class World
{
public:
    static std::vector<std::unique_ptr<World>> discoverLocalWorlds();
    static const fs::path worldsDirectoryPath;

    World(const std::string &name, std::unique_ptr<Generator> &&generator);
    World(const fs::directory_entry &worldDirectory);
    ~World();

    void draw(rl::Vector3 playerPosition, rl::Vector3 playerDirection, int renderDistance);

    std::string name;
    std::chrono::time_point<std::chrono::steady_clock> creationTime;
    std::chrono::time_point<std::chrono::steady_clock> lastPlayedTime;

private:
    void saveToFile();

    fs::directory_entry worldDirectory;
    std::unique_ptr<Generator> generator;
};