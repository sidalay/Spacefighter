#ifndef BASESTATS_HPP
#define BASESTATS_HPP

#include "audio.hpp"
#include "randomizer.hpp"
#include "projectile.hpp"

struct BaseStats
{
    const GameTexture& Textures;
    const GameAudio& Audio;
    const Randomizer& RandomEngine;
    Projectile& Projectiles;
    const raylib::Window& Window;
    raylib::Vector2 ScreenPos{};
    raylib::Vector2 Speed{};
    bool Alive{true};
    float UpdateTime{1.f/14.f};
    float RunningTime{};
    float Health{};
    float MaxSpeed{4.f};
    float BrakeSpeed{2.5f};
    float Scale{4.f};
};

enum class Direction
{
    UP, LEFT, DOWN, RIGHT, SUBTLELEFT, SUBTLERIGHT, NORMAL
};

enum class Stage
{
    I, II, III, IV, V
};

#endif // BASESTATS_HPP