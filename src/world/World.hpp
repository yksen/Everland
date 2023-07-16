#pragma once

#include <chrono>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class World
{
public:
    World(const std::string &name);
    World(const fs::directory_entry &worldDirectory);
    ~World();

    std::string name;
    std::chrono::time_point<std::chrono::steady_clock> creationTime;
    std::chrono::time_point<std::chrono::steady_clock> lastPlayedTime;

private:
    void saveToFile();

    fs::directory_entry worldDirectory;
};

std::vector<std::unique_ptr<World>> discoverLocalWorlds();

static const fs::path worldsDirectoryPath =
    fs::temp_directory_path().parent_path().parent_path().parent_path() / "Roaming\\Everland\\worlds";