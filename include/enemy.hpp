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
          const raylib::Vector2 ScreenPos,
          MonsterType Monster);
    void Tick(float DeltaTime);
    void Draw();
    bool GetAlive() const {return Stats.Alive;}
    void Die() {Stats.Alive = false;}
    void Dying() {Stats.Dying = true;}
    const raylib::Vector2 GetPos() const {return Stats.ScreenPos;}
    const raylib::Vector2 GetCenterPos();
    const raylib::Rectangle GetCollision() const;
private:
    BaseStats Stats;
    MonsterType Monster;
    Sprite Death;
    std::vector<Sprite> Sprites{};

    int SpriteIndex{};
    float Accelerate{3.f};

    void SpriteTick(float DeltaTime);
    void Movement();
    void SwayLeftRight();
    void CheckAttack();
    void CheckOffScreen();
    void SetSpriteIndex();
    void SetMonsterSprite();
    void SetDeathSprite();
    void UpdateScreenPos();
    void CheckDying(float DeltaTime);
};

#endif // ENEMY_HPP