#ifndef MOTHERSHIP_HPP
#define MOTHERSHIP_HPP

#include "enemy.hpp"
#include "ship.hpp"

class Mothership
{
public:
    void Tick(float DeltaTime);
    void Draw();
    const std::vector<Enemy>& GetAliens() const {return Aliens;}

private:
    BaseStats Stats;
    Stage& Level;
    Ship& Spacefighter;
    std::vector<Enemy> Aliens{};

    void Deploy();
    void Load(raylib::Vector2 ScreenPos, MonsterType Type);
    void Recall();
    void CheckShipEnemyCollision();
    void CheckEnemyProjectileCollision(); 
    void CheckShipProjectileCollision();

public:
    Mothership(const GameTexture& Textures,
               const GameAudio& Audio,
               const Randomizer& RandomEngine,
               Projectile& Projectiles,
               const raylib::Window& Window, 
               Stage& CurrentLevel,
               Ship& Spacefighter);
};

#endif // MOTHERSHIP_HPP