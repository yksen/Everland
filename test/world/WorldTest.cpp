#include <world/World.hpp>

#include <gtest/gtest.h>

TEST(WorldTest, updateNeighbors)
{
    World world{"test", std::make_unique<DefaultGenerator>()};
    world.update({0, 0}, 1);

    auto neighbors = world.getChunk({0, 0})->neighbors;
    size_t count = 0;
    for (auto &row : neighbors)
        for (auto &neighbor : row)
            if (neighbor)
                ++count;

    EXPECT_EQ(count, 8);
    EXPECT_TRUE(neighbors[0][0]->neighbors[2][2]->coordinates.Equals({0, 0}));
    EXPECT_TRUE(neighbors[0][1]->neighbors[1][0]->coordinates.Equals({-1, -1}));
}