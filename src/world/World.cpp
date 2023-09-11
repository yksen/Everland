#include "World.hpp"

#include <raylib-cpp.hpp>

#include <algorithm>
#include <fstream>
#include <memory>

const fs::path World::worldsDirectoryPath = std::string(getenv("APPDATA")) + "\\Everland\\worlds";

namespace
{
bool isChunkInRenderDistance(const rl::Vector2 &chunk, const rl::Vector2 &playerChunk, int renderDistance)
{
    return std::abs(chunk.x - playerChunk.x) <= renderDistance && std::abs(chunk.y - playerChunk.y) <= renderDistance;
}
} // namespace

std::vector<std::unique_ptr<World>> World::discoverLocalWorlds()
{
    std::vector<std::unique_ptr<World>> worlds;

    if (!fs::exists(worldsDirectoryPath))
        fs::create_directories(worldsDirectoryPath);

    for (const auto &worldDirectory : fs::directory_iterator(worldsDirectoryPath))
        if (fs::is_directory(worldDirectory))
            worlds.emplace_back(std::make_unique<World>(worldDirectory));

    return worlds;
}

World::World(const std::string &name, std::unique_ptr<Generator> &&generator)
    : name{name}, creationTime{std::chrono::steady_clock::now()}, lastPlayedTime{std::chrono::steady_clock::now()},
      worldDirectory{worldsDirectoryPath / name}, generator{std::move(generator)}
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

void World::update(const rl::Vector2 &playerChunk, int renderDistance)
{
    if (previousPlayerChunk.Equals(playerChunk))
        return;

    generateChunks(playerChunk, renderDistance);
    unloadChunks(playerChunk, renderDistance);

    previousPlayerChunk = playerChunk;
}

void World::generateChunks(const rl::Vector2 &playerChunk, int renderDistance)
{
    for (int x = -renderDistance; x <= renderDistance; ++x)
        for (int z = -renderDistance; z <= renderDistance; ++z)
        {
            const rl::Vector2 chunkPosition = {playerChunk.x + x, playerChunk.y + z};
            auto chunk = getChunk(chunkPosition);
            if (chunk == nullptr)
            {
                chunkCache.push_back(std::make_unique<Chunk>(generator->generateChunk(chunkPosition)));
                addNeighbors(*chunkCache.back());
            }
        }
}

void World::addNeighbors(Chunk &chunk)
{
    for (int x = -1; x <= 1; ++x)
        for (int z = -1; z <= 1; ++z)
        {
            if (x == 0 && z == 0)
                continue;

            const rl::Vector2 neighborPosition = {chunk.coordinates.x + x, chunk.coordinates.y + z};
            auto neighbor = getChunk(neighborPosition);
            if (neighbor != nullptr)
            {
                chunk.neighbors[x + 1][z + 1] = neighbor;
                neighbor->neighbors[-x + 1][-z + 1] = &chunk;
                chunk.buildMesh();
                neighbor->buildMesh();
            }
        }
}

void World::unloadChunks(const rl::Vector2 &playerChunk, int renderDistance)
{
    for (auto chunk = chunkCache.begin(); chunk != chunkCache.end();)
    {
        if (!isChunkInRenderDistance((*chunk)->coordinates, playerChunk, renderDistance))
        {
            removeNeighbors(*chunk->get());
            chunk = chunkCache.erase(chunk);
        }
        else
            ++chunk;
    }
}

void World::removeNeighbors(Chunk &chunk)
{
    for (int x = -1; x <= 1; ++x)
        for (int z = -1; z <= 1; ++z)
        {
            if (x == 0 && z == 0)
                continue;

            const rl::Vector2 neighborPosition = {chunk.coordinates.x + x, chunk.coordinates.y + z};
            auto neighbor = getChunk(neighborPosition);
            if (neighbor != nullptr)
                neighbor->neighbors[-x + 1][-z + 1] = nullptr;
        }
}

void World::draw(bool debugModeEnabled)
{
    for (auto &chunk : chunkCache)
    {
        chunk->draw();
        if (debugModeEnabled)
            chunk->drawChunkBorders();
    }
}

void World::saveInfo()
{
    auto worldFilePath = worldDirectory.path() / "world.info";
    std::ofstream worldFile(worldFilePath, std::ios::out | std::ios::trunc);
    worldFile << name << std::endl;
    worldFile << creationTime.time_since_epoch().count() << std::endl;
    worldFile << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl;
}

Chunk *World::getChunk(const rl::Vector2 &coordinates)
{
    auto chunk = std::find_if(chunkCache.begin(), chunkCache.end(), [coordinates](std::unique_ptr<Chunk> &chunk) {
        return chunk->coordinates == coordinates;
    });
    return (chunk == chunkCache.end()) ? nullptr : chunk->get();
}