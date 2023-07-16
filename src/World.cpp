#include "World.hpp"
#include "raylib.h"

#include <fstream>

World::World(const std::string &name)
    : name{name}, creationTime{std::chrono::steady_clock::now()}, lastPlayedTime{std::chrono::steady_clock::now()},
      worldDirectory{worldsDirectoryPath / name}
{
    if (!fs::exists(worldDirectory))
        fs::create_directories(worldDirectory);
}

World::World(const fs::directory_entry &worldDirectory)
    : name{worldDirectory.path().filename().string()}, worldDirectory(worldDirectory)
{
    std::ifstream worldFile(worldDirectory.path() / "world.info", std::ios::in);
    worldFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int64_t creationTimeCount;
    worldFile >> creationTimeCount;
    creationTime =
        std::chrono::time_point<std::chrono::steady_clock>(std::chrono::steady_clock::duration(creationTimeCount));
    int64_t lastPlayedTimeCount;
    worldFile >> lastPlayedTimeCount;
    lastPlayedTime =
        std::chrono::time_point<std::chrono::steady_clock>(std::chrono::steady_clock::duration(lastPlayedTimeCount));
}

World::~World()
{
    saveToFile();
}

void World::saveToFile()
{
    auto worldFilePath = worldDirectory.path() / "world.info";
    std::ofstream worldFile(worldFilePath, std::ios::out | std::ios::trunc);
    worldFile << name << std::endl;
    worldFile << creationTime.time_since_epoch().count() << std::endl;
    worldFile << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl;
}

std::vector<std::unique_ptr<World>> discoverLocalWorlds()
{
    std::vector<std::unique_ptr<World>> worlds;

    if (!fs::exists(worldsDirectoryPath))
        fs::create_directories(worldsDirectoryPath);

    for (auto &worldDirectory : fs::directory_iterator(worldsDirectoryPath))
        if (fs::is_directory(worldDirectory))
            worlds.emplace_back(std::make_unique<World>(worldDirectory));

    return worlds;
}