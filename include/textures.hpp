#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <raylib-cpp.hpp>

struct GameTexture 
{
    constexpr GameTexture() = default;
    ~GameTexture() = default;
    GameTexture(const GameTexture&) = delete;
    GameTexture(GameTexture&&) = default;
    GameTexture& operator=(const GameTexture&) = delete;
    GameTexture& operator=(GameTexture&&) = default;

    // Alien Sprites
    const raylib::Texture2D Aliens{LoadTexture("sprites/Aliens.png")};
    // Ship Sprites
    const raylib::Texture2D Accelerate{LoadTexture("sprites/ShipAccel.png")};
    const raylib::Texture2D Decelerate{LoadTexture("sprites/ShipDecel.png")};
    const raylib::Texture2D Normal{LoadTexture("sprites/ShipNorm.png")};
    const raylib::Texture2D Projectiles{LoadTexture("sprites/Projectiles.png")};
    // Background Sprites
    const raylib::Texture2D SpaceBackground{LoadTexture("sprites/SpaceBG.png")};
};

#endif // TEXTURES_HPP