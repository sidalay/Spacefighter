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
         const raylib::Window& Window,
         const Shipcolor Shade = Shipcolor::Purple);
    void Tick(float DeltaTime);
    void Draw();
private:
    const GameTexture& Textures;
    const GameAudio& Audio;
    BaseStats Stats{};

    int SpriteIndex{};
    float Brakespeed{Stats.Speed - 1.5f};
    float TurnInTime{};
    float TurnOutTime{};
    float Accelerate{0.05f};
    float Decelerate{0.03f};
    bool Shifting{false};
    
    Shipcolor Shade{};
    Shipstate State{Shipstate::NORMAL}; 
    Direction Heading{Direction::UP};
    Direction PrevHeading{Direction::UP};
    const raylib::Window& Window;
    raylib::Vector2 ScreenPos{};
    raylib::Vector2 PrevScreenPos{};
    raylib::Vector2 Velocity{};
    raylib::Vector2 MaxVelocity{200.f, 200.f};
    std::vector<Sprite> Sprites{};

    void SpriteTick(float DeltaTime);
    void Movement();
    void CheckInput();
    void CheckOffScreen();
    void CheckSpeed();
    void CheckShifting();
    void CheckVelocity();
    void SetSpriteIndex();
    void SetDirectionSprite();
};

#endif