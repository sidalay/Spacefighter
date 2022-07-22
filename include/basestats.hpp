#ifndef BASESTATS_HPP
#define BASESTATS_HPP

#include <vector>
#include "audio.hpp"
#include "sprite.hpp"
#include "randomizer.hpp"

struct BaseStats
{
    bool Alive{true};
    float UpdateTime{1.f/14.f};
    float RunningTime{};
    float Health{};
    float MaxSpeed{4.f};
    float BrakeSpeed{2.5f};
    float Scale{4.f};
    raylib::Vector2 Speed{0.1f, 0.1f};
};

enum class Direction
{
    UP, LEFT, DOWN, RIGHT, SUBTLELEFT, SUBTLERIGHT, NORMAL
};

#endif // BASESTATS_HPP