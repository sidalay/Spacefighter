#include "sprite.hpp"

Sprite::Sprite(const raylib::Texture2D& Texture, const raylib::Vector2I&& MaxFrames, const float UpdateSpeed)
    : Texture{Texture}, MaxFrames{MaxFrames}, UpdateTime{UpdateSpeed} {}

Sprite::Sprite(Sprite&& Object)
    : Texture{std::move(Object.Texture)},
      MaxFrames{std::move(Object.MaxFrames)},
      PreviousFrame{std::move(Object.PreviousFrame)},
      RunningTime{std::move(Object.RunningTime)},
      UpdateTime{std::move(Object.UpdateTime)} {}

Sprite& Sprite::operator=(Sprite&& Object)
{
    if (this == &Object)
    {
        return *this;
    }

    this->PreviousFrame = std::move(Object.PreviousFrame);
    this->RunningTime = std::move(Object.RunningTime);
    this->UpdateTime = std::move(Object.UpdateTime);
    return *this;
}

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

raylib::Rectangle Sprite::GetSourceRec() const
{
    return Rectangle
    {
        static_cast<float>(Frame.x * Texture.width / MaxFrames.x),
        static_cast<float>(Frame.y * Texture.height / MaxFrames.y),
        static_cast<float>(Texture.width / MaxFrames.x),
        static_cast<float>(Texture.height / MaxFrames.y)
    };
}

raylib::Rectangle Sprite::GetPosRec(const raylib::Vector2& ScreenPos, const float Scale) const
{
    return Rectangle
    {
        (ScreenPos.x),
        (ScreenPos.y),
        static_cast<float>(Texture.width/MaxFrames.x) * Scale,
        static_cast<float>(Texture.height/MaxFrames.y) * Scale
    };
}