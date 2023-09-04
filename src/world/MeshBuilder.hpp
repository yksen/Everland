#pragma once

#include "Generator.hpp"

#include <magic_enum_all.hpp>
#include <raylib-cpp.hpp>

namespace me
{
using namespace magic_enum;
using namespace magic_enum::containers;
} // namespace me
namespace rl = raylib;

struct Chunk;

enum class Direction
{
    Top,
    Bottom,
    North,
    South,
    East,
    West,
};

constexpr me::array<Direction, Vector3> cubeNormals{
    0.f,  1.f,  0.f,  // Top
    0.f,  -1.f, 0.f,  // Bottom
    0.f,  0.f,  1.f,  // North
    0.f,  0.f,  -1.f, // South
    -1.f, 0.f,  0.f,  // East
    1.f,  0.f,  0.f,  // West
};

constexpr me::array<Direction, std::array<Vector3, 6>> cubeFaces{
    0.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f, // Top
    0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f, //
    0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f, // Bottom
    0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f, 1.f, //
    0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f, // North
    0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, 1.f, //
    0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.f, // South
    0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, //
    0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, // East
    0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 0.f, //
    1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f, // West
    1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 1.f, //
};

class MeshBuilder
{
public:
    MeshBuilder();

    Mesh buildMesh(const Chunk &chunk);
};