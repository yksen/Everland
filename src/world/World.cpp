#include "World.hpp"
#include "raylib-cpp.hpp"

#include <fstream>
#include <memory>

const std::string World::worldsDirectoryPath = std::string(getenv("APPDATA")) + "\\Everland\\worlds";

std::vector<std::unique_ptr<World>> World::discoverLocalWorlds()
{
    std::vector<std::unique_ptr<World>> worlds;

    if (!fs::exists(worldsDirectoryPath))
        fs::create_directories(worldsDirectoryPath);

    for (auto &worldDirectory : fs::directory_iterator(worldsDirectoryPath))
        if (fs::is_directory(worldDirectory))
            worlds.emplace_back(std::make_unique<World>(worldDirectory.path().filename().string()));

    return worlds;
}

World::World(const std::string &name, std::unique_ptr<Generator> &&generator)
    : name{name}, creationTime{std::chrono::steady_clock::now()}, lastPlayedTime{std::chrono::steady_clock::now()},
      worldDirectory{worldsDirectoryPath + "\\" + name}, generator{std::move(generator)}
{
    if (!fs::exists(worldDirectory))
        fs::create_directories(worldDirectory);
}

World::World(const std::string &worldDirectory) : name{worldDirectory}, worldDirectory(worldDirectory)
{
    std::ifstream worldFile(worldDirectory + "\\world.info", std::ios::in);
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
    saveInfo();
}

void World::draw(rl::Vector3 playerPosition, rl::Vector3 playerDirection, int renderDistance)
{
    for (int x = -renderDistance; x <= renderDistance; ++x)
        for (int y = -renderDistance; y <= renderDistance; ++y)
            for (int z = -renderDistance; z <= renderDistance; ++z)
            {
                rl::Vector2 scaledPlayerPosition = {playerPosition.x / Chunk::size, playerPosition.z / Chunk::size};
                rl::Vector2 chunkPosition = {scaledPlayerPosition.x + x, scaledPlayerPosition.y + z};
                auto chunk = generator->generateChunk(chunkPosition);
                chunk.draw(playerPosition, playerDirection);
            }
}

void World::saveInfo()
{
    auto worldFilePath = worldDirectory + "\\world.info";

    std::string worldInfo = name + '\n' + std::to_string(creationTime.time_since_epoch().count()) + '\n' +
                            std::to_string(std::chrono::steady_clock::now().time_since_epoch().count());

    SaveFileText(worldFilePath.c_str(), const_cast<char *>(worldInfo.c_str()));
}