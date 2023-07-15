#include "World.hpp"

World::World(const std::string &name)
    : name{name}, creationTime{std::chrono::steady_clock::now()}
{
}