#ifndef SHIP_HPP
#define SHIP_HPP

// #include <vector>
#include "basecharacter.hpp"
// #include "projectile.hpp"

class Ship : BaseCharacter
{
public:
    Ship();
    Ship(const GameTexture& Textures, const GameAudio& Audio, const raylib::Vector2I& Screen);
    void Tick(float DeltaTime) override;
    void SetTexture();
private:
    float SourceY{};
    float BulletWidth{};
    float BulletHeight{};
    raylib::Vector2I Screen{};
    std::vector<Sprite> Sprites{};
};

#endif