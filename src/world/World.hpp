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
    explicit World(const fs::directory_entry &worldDirectory);

    void update(const rl::Vector2 &playerChunk, int renderDistance);
    void draw(bool debugModeEnabled);
    void saveInfo();
    Chunk *getChunk(const rl::Vector2 &coordinates);

    std::string name;
    std::chrono::time_point<std::chrono::steady_clock> creationTime;
    std::chrono::time_point<std::chrono::steady_clock> lastPlayedTime;

private:
    void generateChunks(const rl::Vector2 &playerChunk, int renderDistance);
    void addNeighbors(Chunk &chunk);
    void unloadChunks(const rl::Vector2 &playerChunk, int renderDistance);
    void removeNeighbors(Chunk &chunk);

    fs::directory_entry worldDirectory;
    std::unique_ptr<Generator> generator;
    std::deque<std::unique_ptr<Chunk>> chunkCache;
    rl::Vector2 previousPlayerChunk{0.5F};
};