#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "basestats.hpp"

enum class MonsterType
{
    Purple, Yellow, Aqua, Pink, Red, Orange, Blue, Green
};

class Enemy
{
public:
    Enemy(const GameTexture& Textures,
          const GameAudio& Audio,
          const Randomizer& RandomEngine,
          Projectile& Projectiles,
          const raylib::Window& Window,
          MonsterType Monster);
    void Tick(float DeltaTime);
    void Draw();
    const raylib::Vector2 GetPos() const {return Stats.ScreenPos;}
    const raylib::Rectangle GetCollision() const;
private:
    BaseStats Stats;
    MonsterType Monster;
    std::vector<Sprite> Sprites{};

    int SpriteIndex{};
    float Accelerate{0.05f};
    float Decelerate{0.03f};

    void SpriteTick(float DeltaTime);
    void Movement();
    void CheckAttack();
    void CheckOffScreen();
    void SetSpriteIndex();
    void SetMonsterSprite();
    void UpdateScreenPos();
};

#endif // ENEMY_HPP