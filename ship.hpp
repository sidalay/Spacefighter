#ifndef SHIP_HPP
#define SHIP_HPP

#include "basecharacter.hpp"
#include "window.hpp"

class Ship : BaseCharacter
{
private:
    Texture2D idle {LoadTexture("sprites/ShipNormal_Sprites.png")};
    Texture2D accel {LoadTexture("sprites/ShipAccel_Sprites.png")};
    Texture2D decel {LoadTexture("sprites/ShipDecel_Sprites.png")};
    Texture2D projectile {LoadTexture("sprites/Projectile_Sprites.png")};
    float sourceY{};            // Change the Y portion of the sprite being drawn
    float bulletWidth{};
    float bulletHeight{};
    Vector2 ScreenPos {Window::Dimension.x/2, Window::Dimension.y/2};

public:
    Ship();
    ~Ship();
    void tick(float deltaTime) override;
};

#endif