#ifndef SHIP_H
#define SHIP_H

#include "basecharacter.h"
#include "window.h"

class Ship : BaseCharacter
{
private:
    Texture2D idle {LoadTexture("sprites/ShipNormal_Sprites.png")};
    Texture2D accel {LoadTexture("sprites/ShipAccel_Sprites.png")};
    Texture2D decel {LoadTexture("sprites/ShipDecel_Sprites.png")};
    Texture2D projectile {LoadTexture("sprites/Projectile_Sprites.png")};
    float sourceY{};
    float bulletWidth{};
    float bulletHeight{};
    Vector2 ScreenPos {Window::Dimension.x/2, Window::Dimension.y/2};

public:
    Ship();
    ~Ship();
    void tick(float deltaTime) override;
};

#endif