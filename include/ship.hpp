#ifndef SHIP_HPP
#define SHIP_HPP

#include "basestats.hpp"

enum class Shipcolor
{
    Red, Purple, Green, Blue
};

enum class Shipstate
{
    ACCELERATE, DECELERATE, NORMAL
};

class Ship
{
public:
    Ship(const GameTexture& Textures, 
         const GameAudio& Audio,
         const Randomizer& RandomEngine,
         Projectile& Projectiles,
         const raylib::Window& Window,
         const Shipcolor ShipShade = Shipcolor::Purple);
    void Tick(float DeltaTime);
    void Draw();
    void Dying() {Stats.Dying = true;}
    const raylib::Vector2 GetPos() const {return Stats.ScreenPos;}
    const raylib::Vector2 GetCenterPos();
    const raylib::Vector2 GetSpeed() const {return Stats.Speed;}
    const raylib::Rectangle GetCollision() const;
private:
    BaseStats Stats;
    Shipcolor Shade{};
    Shipstate State{Shipstate::NORMAL}; 
    Direction Heading{Direction::UP};
    Sprite Death;
    std::vector<Sprite> Sprites{};

    int SpriteIndex{};
    float TurnInTime{};
    float TurnOutTime{};
    float Accelerate{0.05f};
    float Decelerate{0.03f};

    void SpriteTick(float DeltaTime);
    void Movement();
    void CheckAccel();
    void CheckDecel();
    void CheckInput();
    void CheckAttack();
    void CheckDying(float DeltaTime);
    void CheckOffScreen();
    void SetDirectionSprite();
    void SetSpriteIndex();
    void UpdateScreenPos();
};

#endif