#ifndef BASESTATS_HPP
#define BASESTATS_HPP

#include "audio.hpp"
#include "randomizer.hpp"
#include "projectile.hpp"

struct BaseStats
{
    BaseStats(const GameTexture& Textures,
              const GameAudio& Audio,
              const Randomizer& RandomEngine,
              Projectile& Projectiles,
              const raylib::Window& Window,
              const raylib::Vector2 ScreenPos);
    ~BaseStats() = default;
    BaseStats(const BaseStats&) = delete;
    BaseStats(BaseStats&& Object);
    BaseStats& operator=(const BaseStats&) = delete;
    BaseStats& operator=(BaseStats&& Object);

    const GameTexture& Textures;
    const GameAudio& Audio;
    const Randomizer& RandomEngine;
    Projectile& Projectiles;
    const raylib::Window& Window;
    raylib::Vector2 ScreenPos{};
    raylib::Vector2 Speed{};
    bool Alive{true};
    bool Dying{false};
    bool CollisionOn{true};
    bool TakingDamage{false};
    float UpdateTime{1.f/14.f};
    float RunningTime{};
    float AttackTime{};
    float CooldownTime{};
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