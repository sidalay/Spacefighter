#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <raylib.h>

struct GameTexture 
{
    constexpr GameTexture() = default;
    ~GameTexture();
    GameTexture(const GameTexture&) = delete;
    GameTexture(GameTexture&&) = default;
    GameTexture& operator=(const GameTexture&) = delete;
    GameTexture& operator=(GameTexture&&) = default;

    // Alien Sprites
    const Texture2D Aliens{LoadTexture("sprites/Aliens.png")};
    // Ship Sprites
    const Texture2D Accelerate{LoadTexture("sprites/ShipAccel.png")};
    const Texture2D Decelerate{LoadTexture("sprites/ShipDecel.png")};
    const Texture2D Normal{LoadTexture("sprites/ShipNorm.png")};
    const Texture2D Projectiles{LoadTexture("sprites/Projectiles.png")};
    // Background Sprites
    const Texture2D SpaceBackground{LoadTexture("sprites/SpaceBG.png")};
};

#endif // TEXTURES_HPP