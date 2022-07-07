#include "sprite.hpp"

Sprite::Sprite(const raylib::Texture2D& Texture, const raylib::Vector2I&& MaxFrames, const float UpdateSpeed)
    : Texture{Texture}, MaxFrames{MaxFrames}, UpdateTime{UpdateSpeed} {}

void Sprite::Tick(float DeltaTime)
{
    // update animation frame
    RunningTime += DeltaTime;
    if (RunningTime >= UpdateTime) {
        PreviousFrame = Frame.x;
        ++Frame.x;
        RunningTime = 0.f;
        if (Frame.x > MaxFrames.x) {
            Frame.x = 0;
        }
    }
}

raylib::Rectangle Sprite::GetSourceRec()
{
    Rectangle Source {
        static_cast<float>(Frame.x * Texture.width / MaxFrames.x),
        static_cast<float>(Frame.y * Texture.height / MaxFrames.y),
        static_cast<float>(Texture.width / MaxFrames.x),
        static_cast<float>(Texture.height / MaxFrames.y)
    };
    return Source;
}

raylib::Rectangle Sprite::GetPosRec(raylib::Vector2& ScreenPos, const float Scale)
{
    Rectangle Destination {
        (ScreenPos.x),
        (ScreenPos.y),
        static_cast<float>(Texture.width/MaxFrames.x) * Scale,
        static_cast<float>(Texture.height/MaxFrames.y) * Scale
    };
    return Destination;
}