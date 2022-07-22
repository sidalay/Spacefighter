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
         const Shipcolor Shade = Shipcolor::Purple);
    void Tick(float DeltaTime);
    void Draw();
    const raylib::Vector2 GetPos() const {return ScreenPos;}
    const raylib::Vector2 GetCenterPos();
    const raylib::Vector2 GetSpeed() const {return Stats.Speed;}
    const raylib::Rectangle GetCollision() const;
private:
    const GameTexture& Textures;
    const GameAudio& Audio;
    const Randomizer& RandomEngine;
    Projectile& Projectiles;
    BaseStats Stats{};

    int SpriteIndex{};
    float TurnInTime{};
    float TurnOutTime{};
    float Accelerate{0.05f};
    float Decelerate{0.03f};
    
    Shipcolor Shade{};
    Shipstate State{Shipstate::NORMAL}; 
    Direction Heading{Direction::UP};
    Direction PrevHeading{Direction::UP};
    const raylib::Window& Window;
    raylib::Vector2 ScreenPos{};
    std::vector<Sprite> Sprites{};

    void SpriteTick(float DeltaTime);
    void Movement();
    void CheckAccel();
    void CheckDecel();
    void CheckInput();
    void CheckAttack();
    void CheckOffScreen();
    void SetDirectionSprite();
    void SetSpriteIndex();
    void UpdateScreenPos();
};

#endif