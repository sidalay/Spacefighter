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

    struct Circle
    {
        int x;
        int y;
        float radius;
    };
};

struct Sprite
{
    Sprite() = default;
    explicit Sprite(const raylib::Texture& Texture, 
                    const raylib::Vector2I&& MaxFrames = raylib::Vector2I{1,1}, 
                    const float UpdateSpeed = 1.f/8.f);
    ~Sprite() = default;
    Sprite(const Sprite&) = delete;
    Sprite(Sprite&& Object);
    Sprite& operator=(const Sprite&) = delete;
    Sprite& operator=(Sprite&& Object);
    void Tick(float DeltaTime);
    constexpr int GetTextureWidth(float Scale = 1.f) const {return (Texture.width/MaxFrames.x) * static_cast<int>(Scale);}
    constexpr int GetTextureHeight(float Scale = 1.f) const {return (Texture.height/MaxFrames.y) * static_cast<int>(Scale);}
    const raylib::Texture& GetTexture() const {return Texture;}
    raylib::Rectangle GetSourceRec() const;
    raylib::Rectangle GetPosRec(const raylib::Vector2& ScreenPos, const float Scale) const;
    raylib::Vector2I Frame{};
private:
    const raylib::Texture& Texture{};
    const raylib::Vector2I MaxFrames{};
    int PreviousFrame{};
    float RunningTime{};
    float UpdateTime{1.f/8.f};
};

#endif // SPRITE_HPP