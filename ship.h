#ifndef SHIP_H
#define SHIP_H

#include "basecharacter.h"

class Ship : BaseCharacter
{
private:
    Texture2D idle {LoadTexture("sprites/ShipNormal_Sprites.png")};
    Texture2D accel {LoadTexture("sprites/ShipAccel_Sprites.png")};
    Texture2D decel {LoadTexture("sprites/ShipDecel_Sprites.png")};
    float sourceY{};

public:
    Ship();
    void tick(float deltaTime) override;
};

#endif