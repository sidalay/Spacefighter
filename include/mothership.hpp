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
    void Deploy();
    void Recall(float DeltaTime);
    void Load(raylib::Vector2 ScreenPos, MonsterType Type);
    std::vector<Enemy>& GetAliens() {return Aliens;} 
private:
    BaseStats Stats;
    Stage& Level;
    std::vector<Enemy> Aliens{};
};

#endif // MOTHERSHIP_HPP