#ifndef SHIP_HPP
#define SHIP_HPP

#include "basecharacter.hpp"

enum class Shipcolor
{
    Red, Purple, Green, Blue    
};

enum class Shipstate
{
    ACCELERATE, DECELERATE, NORMAL
};

class Ship : BaseCharacter
{
public:
    Ship(const GameTexture& Textures, 
         const GameAudio& Audio,
         const raylib::Window& Window,
         const Shipcolor Shade = Shipcolor::Purple);
    void Tick(float DeltaTime) override;
    void Draw();
private:
    const GameTexture& Textures;
    const GameAudio& Audio;

    int SpriteIndex{};
    float Brakespeed{Speed - 1.5f};
    float TurnInTime{};
    float TurnOutTime{};
    float MaxVelocity{100.f};
    float Accelerate{0.05f};
    float Decelerate{0.03f};
    
    Shipcolor Shade{};
    Shipstate State{Shipstate::NORMAL}; 
    Direction Flying{Direction::UP};
    const raylib::Window& Window;
    raylib::Vector2 ScreenPos{};
    raylib::Vector2 Velocity{};
    std::vector<Sprite> Sprites{};

    void SpriteTick(float DeltaTime);
    void Movement();
    void WithinScreen();
    void CheckInput();
    void CheckDirection();
    void CheckSpriteIndex();
    void CheckOffScreen();
    void CheckSpeed();
    void CheckVelocity();
};

#endif