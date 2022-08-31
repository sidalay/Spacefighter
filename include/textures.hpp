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

    const raylib::Texture Aliens{"sprites/Aliens.png"};
    const raylib::Texture Asteroid{"sprites/Asteroid.png"};
    const raylib::Texture Accelerate{"sprites/ShipAccel.png"};
    const raylib::Texture Decelerate{"sprites/ShipDecel.png"};
    const raylib::Texture Death{"sprites/Death.png"};
    const raylib::Texture Roll{"sprites/ShipRoll.png"};
    const raylib::Texture Normal{"sprites/ShipNorm.png"};
    const raylib::Texture Projectiles{"sprites/Projectiles.png"};
    const raylib::Texture SpaceBackground{"sprites/SpaceBG.png"};
    const raylib::Texture SpaceBackgroundOverlay{"sprites/SpaceBGOverlay.png"};
};

#endif // TEXTURES_HPP