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

class Chunk;

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
    0.F,  1.F,  0.F,  // Top
    0.F,  -1.F, 0.F,  // Bottom
    0.F,  0.F,  1.F,  // North
    0.F,  0.F,  -1.F, // South
    -1.F, 0.F,  0.F,  // East
    1.F,  0.F,  0.F,  // West
};

constexpr me::array<Direction, std::array<Vector3, 6>> cubeFaces{
    0.F, 1.F, 0.F, 1.F, 1.F, 1.F, 1.F, 1.F, 0.F, // Top
    0.F, 1.F, 0.F, 0.F, 1.F, 1.F, 1.F, 1.F, 1.F, //
    0.F, 0.F, 0.F, 1.F, 0.F, 0.F, 1.F, 0.F, 1.F, // Bottom
    0.F, 0.F, 0.F, 1.F, 0.F, 1.F, 0.F, 0.F, 1.F, //
    0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 1.F, 1.F, 1.F, // North
    0.F, 0.F, 1.F, 1.F, 1.F, 1.F, 0.F, 1.F, 1.F, //
    0.F, 0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 0.F, 0.F, // South
    0.F, 0.F, 0.F, 0.F, 1.F, 0.F, 1.F, 1.F, 0.F, //
    0.F, 0.F, 0.F, 0.F, 0.F, 1.F, 0.F, 1.F, 1.F, // East
    0.F, 0.F, 0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 0.F, //
    1.F, 0.F, 0.F, 1.F, 1.F, 1.F, 1.F, 0.F, 1.F, // West
    1.F, 0.F, 0.F, 1.F, 1.F, 0.F, 1.F, 1.F, 1.F, //
};

class MeshBuilder
{
public:
    MeshBuilder() = default;

    Mesh buildMesh(const Chunk &chunk) const;
};