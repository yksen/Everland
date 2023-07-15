#pragma once

#include <chrono>
#include <string>

class World
{
public:
    World(const std::string &name);

    std::string name;
    const std::chrono::time_point<std::chrono::steady_clock> creationTime;

private:
};