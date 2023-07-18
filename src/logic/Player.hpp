#pragma once

class Player
{
public:
    Player() = default;
    Player(const Player &) = delete;
    Player &operator=(const Player &) = delete;

private:
};