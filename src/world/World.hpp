#pragma once

#include <world/Generator.hpp>

#include <raylib-cpp.hpp>

#include <chrono>
#include <deque>
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

    void update(const rl::Vector2 &playerChunk, int renderDistance);
    void draw(const rl::Camera &playerCamera, bool debugModeEnabled);
    Chunk *getChunk(const rl::Vector2 &coordinates);

    std::string name;
    std::chrono::time_point<std::chrono::steady_clock> creationTime;
    std::chrono::time_point<std::chrono::steady_clock> lastPlayedTime;

private:
    void updateNeighbors(Chunk &chunk);
    void saveInfo();

    fs::directory_entry worldDirectory;
    std::unique_ptr<Generator> generator;
    std::deque<Chunk> chunkCache;
    rl::Vector2 previousPlayerChunk{0, 0};
};