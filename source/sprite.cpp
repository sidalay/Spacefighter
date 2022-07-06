#include "sprite.hpp"

Sprite::Sprite(const raylib::Texture2D& Texture, const raylib::Vector2I& MaxFrames, const float UpdateSpeed)
    : MaxFrames{MaxFrames}, Texture{Texture}, UpdateTime{UpdateSpeed} {}

void Sprite::Tick(float DeltaTime)
{
    // update animation frame
    RunningTime += DeltaTime;
    if (RunningTime >= UpdateTime) {
        PreviousFrame = CurrentFrame.x;
        ++CurrentFrame.x;
        RunningTime = 0.f;
        if (CurrentFrame.x > MaxFrames.x) {
            CurrentFrame.x = 0;
        }
    }
}

raylib::Rectangle Sprite::GetSourceRec()
{
    Rectangle Source {
        static_cast<float>(CurrentFrame.x * Texture.width / MaxFrames.x),
        static_cast<float>(CurrentFrame.y * Texture.height / MaxFrames.y),
        static_cast<float>(Texture.width / MaxFrames.x),
        static_cast<float>(Texture.height / MaxFrames.y)
    };
    return Source;
}

raylib::Rectangle Sprite::GetPosRec(const raylib::Vector2I& ScreenPos, const float Scale)
{
    Rectangle Destination {
        static_cast<float>(ScreenPos.x),
        static_cast<float>(ScreenPos.y),
        static_cast<float>(Texture.width/MaxFrames.x) * Scale,
        static_cast<float>(Texture.height/MaxFrames.y) * Scale
    };
    return Destination;
}