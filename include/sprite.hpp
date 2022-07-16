#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "textures.hpp"

namespace raylib 
{
    struct Vector2I
    {
        int x;
        int y;
    };
};

struct Sprite
{
    Sprite() = default;
    explicit Sprite(const raylib::Texture& Texture, const raylib::Vector2I&& MaxFrames = raylib::Vector2I{1,1}, const float UpdateSpeed = 1.f/8.f);
    void Tick(float DeltaTime);
    constexpr int GetTextureWidth() const {return Texture.width/MaxFrames.x;}
    constexpr int GetTextureHeight() const {return Texture.height/MaxFrames.y;}
    raylib::Rectangle GetSourceRec();
    raylib::Rectangle GetPosRec(raylib::Vector2& ScreenPos, const float Scale);

    const raylib::Texture& Texture{};
    raylib::Vector2I MaxFrames{};
    raylib::Vector2I Frame{};
    int PreviousFrame{};
    float RunningTime{};
    const float UpdateTime{1.f/8.f};
};

#endif // SPRITE_HPP