#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <raylib-cpp.hpp>

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
    explicit Sprite(const raylib::Texture2D& Texture, const raylib::Vector2I& MaxFrames = raylib::Vector2I{1,1}, const float UpdateSpeed = 1.f/8.f);
    void Tick(float DeltaTime);
    raylib::Rectangle GetSourceRec();
    raylib::Rectangle GetPosRec(const raylib::Vector2I& ScreenPos, const float Scale);
    raylib::Vector2I MaxFrames{};
    raylib::Vector2I CurrentFrame{};
private:
    const Texture2D& Texture{};
    int PreviousFrame{};
    float RunningTime{};
    const float UpdateTime{1.f/8.f};
};

#endif // SPRITE_HPP