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
    const raylib::Vector2& SpacefighterPos;
    std::vector<Sprite> Sprites{};
    int SpriteIndex{};
    float Accelerate{3.f};

    void SpriteTick(float DeltaTime);
    void Movement();
    void SwayLeftRight();
    void CheckAttack(float DeltaTime);
    void CheckOffScreen();
    void SetSpriteIndex();
    void SetMonsterSprite();
    void SetDeathSprite();
    void UpdateScreenPos();
    void CheckDying(float DeltaTime);

public:
    Enemy(const GameTexture& Textures,
          const GameAudio& Audio,
          const Randomizer& RandomEngine,
          Projectile& Projectiles,
          const raylib::Window& Window,
          const raylib::Vector2 ScreenPos,
          const raylib::Vector2& SpacefighterPos,
          MonsterType Monster);
    ~Enemy() = default;
    Enemy(const Enemy&) = delete;
    Enemy(Enemy&& Object);
    Enemy& operator=(const Enemy&) = delete;
    Enemy& operator=(Enemy&& Object);
};

#endif // ENEMY_HPP