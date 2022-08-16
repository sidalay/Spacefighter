#include "mothership.hpp"
#include <algorithm>
#include <iostream>

Mothership::Mothership(const GameTexture& Textures,
                       const GameAudio& Audio,
                       const Randomizer& RandomEngine,
                       Projectile& Projectiles,
                       const raylib::Window& Window, 
                       Stage& CurrentLevel)
    : Stats{Textures, Audio, RandomEngine, Projectiles, Window, raylib::Vector2{}}, Level{CurrentLevel} 
    {
        Aliens.reserve(10);
    };

void Mothership::Tick(float DeltaTime)
{
    for (auto& Alien:Aliens)
    {
        Alien.Tick(DeltaTime);
    }
    Deploy();
    if (CheckProjectileCollision())
    {
        Recall();
    }
}

void Mothership::Draw()
{
    for (auto& Alien:Aliens)
    {
        Alien.Draw();
    }
}

void Mothership::Deploy()
{
    if (IsKeyPressed(KEY_F2))
    {
        Load(raylib::Vector2{0.f, 64.f}, MonsterType::Orange);
    }
    else if (IsKeyPressed(KEY_F3))
    {
        Load(raylib::Vector2{0.f, 128.f}, MonsterType::Pink);
    }
    else if (IsKeyPressed(KEY_F4))
    {
        Load(raylib::Vector2{0.f, 192.f}, MonsterType::Purple);
    }
    else if (IsKeyPressed(KEY_F5))
    {
        Load(raylib::Vector2{0.f, 256.f}, MonsterType::Aqua);
    }
    else if (IsKeyPressed(KEY_F6))
    {
        Load(raylib::Vector2{0.f, 320.f}, MonsterType::Blue);
    }
    else if (IsKeyPressed(KEY_F7))
    {
        Load(raylib::Vector2{0.f, 384.f}, MonsterType::Green);
    }
    else if (IsKeyPressed(KEY_F8))
    {
        Load(raylib::Vector2{0.f, 448.f}, MonsterType::Red);
    }
    else if (IsKeyPressed(KEY_F9))
    {
        Load(raylib::Vector2{0.f, 512.f}, MonsterType::Yellow);
    }
}

void Mothership::Load(raylib::Vector2 ScreenPos, MonsterType Type)
{
    Aliens.emplace_back(
        Stats.Textures, 
        Stats.Audio, 
        Stats.RandomEngine, 
        Stats.Projectiles, 
        Stats.Window, 
        ScreenPos, 
        Type);
}

void Mothership::Recall()
{
    std::erase_if(Aliens, [](auto&& Alien) {
        return !Alien.GetAlive();
    });
}

bool Mothership::CheckProjectileCollision()
{
    std::vector<raylib::Circle> Bullets{Stats.Projectiles.GetCollision()};

    for (auto& Alien:Aliens)
    {
        for (auto& Bullet:Bullets)
        {
            if (CheckCollisionCircleRec(raylib::Vector2{static_cast<float>(Bullet.x), static_cast<float>(Bullet.y)}, Bullet.radius, Alien.GetCollision()))
            {
                Alien.Death();
                return true;
            }
        }
    }
    return false;
}
