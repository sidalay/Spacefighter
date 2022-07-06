#ifndef SHIP_HPP
#define SHIP_HPP

// #include <vector>
#include "basecharacter.hpp"
// #include "projectile.hpp"

class Ship : BaseCharacter
{
public:
    Ship();
    ~Ship();
    void Tick(float DeltaTime) override;
private:
    float SourceY{};            // Change the Y portion of the sprite being drawn
    float BulletWidth{};
    float BulletHeight{};
    Vector2 ScreenPos{};
};

#endif