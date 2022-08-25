#ifndef MOTHERSHIP_HPP
#define MOTHERSHIP_HPP

#include "enemy.hpp"

class Mothership
{
public:
    Mothership(const GameTexture& Textures,
               const GameAudio& Audio,
               const Randomizer& RandomEngine,
               Projectile& Projectiles,
               const raylib::Window& Window, 
               Stage& CurrentLevel);
    void Tick(float DeltaTime);
    void Draw();
    const std::vector<Enemy>& GetAliens() const {return Aliens;}
private:
    BaseStats Stats;
    Stage& Level;
    std::vector<Enemy> Aliens{};

    void Deploy();
    void Load(raylib::Vector2 ScreenPos, MonsterType Type);
    void Recall();
    void CheckProjectileCollision(); 
};

#endif // MOTHERSHIP_HPP