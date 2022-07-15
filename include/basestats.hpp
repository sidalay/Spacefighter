#ifndef BASESTATS_HPP
#define BASESTATS_HPP

#include <vector>
#include "audio.hpp"
#include "sprite.hpp"

enum class Direction
{
    UP, LEFT, DOWN, RIGHT, SUBTLELEFT, SUBTLERIGHT, NORMAL
};

struct BaseStats
{
    bool Alive{true};
    float UpdateTime{1.f/14.f};
    float RunningTime{};
    float Health{};
    float MaxSpeed{4.f};
    float BrakeSpeed{2.5f};
    float SpeedX{0.1f};
    float SpeedY{0.1f};
    float Scale{4.f};
};

#endif // BASESTATS_HPP