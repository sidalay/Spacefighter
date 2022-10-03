#include "mothership.hpp"
#include <algorithm>

Mothership::Mothership(const GameTexture& Textures,
                       const GameAudio& Audio,
                       const Randomizer& RandomEngine,
                       Projectile& Projectiles,
                       const raylib::Window& Window, 
                       Stage& CurrentLevel,
                       Ship& Spacefighter)
    : Stats
      {
        Textures, 
        Audio, 
        RandomEngine, 
        Projectiles, 
        Window, 
        raylib::Vector2{}
      }, 
      Level{CurrentLevel},
      Spacefighter{Spacefighter},
      Levels{Editor.GetLevel(1)} {};

void Mothership::Tick(float DeltaTime)
{
    for (auto& Alien:Aliens)
    {
        Alien.Tick(DeltaTime);
    }
    Deploy();
    CheckEnemyProjectileCollision();
    CheckShipProjectileCollision();
    Recall();
    CheckShipEnemyCollision();
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
    Stats.RunningTime += GetFrameTime();

    if (Stats.RunningTime >= 5.f) 
    {
        auto Iterator {Levels.begin()};
        if (Iterator != Levels.end()) // Construct Aliens & erase from vector
        {
            Load(Iterator->first, Iterator->second);
            Levels.erase(Iterator);
        }
        else // If vector is empty load next level
        {
            LoadLevel();
        }
        Stats.RunningTime = 3.f;
    }
}

void Mothership::Load(Spawn SpawnPoint, MonsterType Type)
{
    Aliens.emplace_back(
        Stats.Textures, 
        Stats.Audio, 
        Stats.RandomEngine, 
        Stats.Projectiles, 
        Stats.Window, 
        raylib::Vector2{0.f,0.f},
        Spacefighter.GetPos(),
        SpawnPoint,
        Type);
}

void Mothership::LoadLevel()
{
    if (CurrentLevel < Editor.GetNumberOfLevels()) 
    {
        Levels = Editor.GetLevel(++CurrentLevel);
    }
}

void Mothership::Recall()
{
    std::erase_if(Aliens, [](auto&& Alien) {
        return !Alien.GetAlive();
    });
}

void Mothership::CheckShipEnemyCollision()
{
    for (auto& Alien:Aliens)
    {
        if (CheckCollisionRecs(Alien.GetCollision(), Spacefighter.GetCollision()))
        {
            Alien.Dying();
            Spacefighter.TakeDamage();
        }
    }
}

void Mothership::CheckEnemyProjectileCollision()
{
    std::vector<raylib::Circle> Bullets{Stats.Projectiles.GetShipAtkCollision()};

    for (auto& Alien:Aliens)
    {
        for (int i = 0; i < static_cast<int>(Bullets.size()); ++i)
        {
            if (Stats.Projectiles.GetPositions().at(i).second == false &&
                CheckCollisionCircleRec(raylib::Vector2{static_cast<float>(Bullets.at(i).x), static_cast<float>(Bullets.at(i).y)}, Bullets.at(i).radius, Alien.GetCollision()))
            {
                Alien.Dying();
                Stats.Projectiles.SetShipAtkCollided(i);
            }
        }
    }
}

void Mothership::CheckShipProjectileCollision()
{
    std::vector<raylib::Circle> Bullets{Stats.Projectiles.GetEnemyAtkCollision()};

    for (int i = 0; i < static_cast<int>(Bullets.size()); ++i)
    {
        if (Stats.Projectiles.GetEnemyPositions().at(i).second == false &&
            CheckCollisionCircleRec(raylib::Vector2{static_cast<float>(Bullets.at(i).x), static_cast<float>(Bullets.at(i).y)}, Bullets.at(i).radius, Spacefighter.GetCollision()))
        {
            Spacefighter.TakeDamage();
            Stats.Projectiles.SetEnemyAtkCollided(i);
        }
    }
}