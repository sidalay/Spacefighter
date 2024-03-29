#include "sprite.hpp"

Sprite::Sprite(const raylib::Texture2D& Texture, 
               const std::string_view Name, 
               const raylib::Vector2I&& MaxFrames, 
               const float UpdateSpeed)
    : Texture{Texture}, Name{Name}, MaxFrames{MaxFrames}, UpdateTime{UpdateSpeed} {}

Sprite::Sprite(Sprite&& Object)
    : Frame{std::move(Object.Frame)},
      Texture{std::move(Object.Texture)},
      Name{std::move(Object.Name)},
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
    
    this->Frame = std::move(Object.Frame);
    this->PreviousFrame = std::move(Object.PreviousFrame);
    this->RunningTime = std::move(Object.RunningTime);
    this->UpdateTime = std::move(Object.UpdateTime);
    return *this;
}

void Sprite::Tick(float DeltaTime)
{
    // update animation frame
    RunningTime += DeltaTime;
    if (RunningTime >= UpdateTime) 
    {
        PreviousFrame = Frame.x;
        ++Frame.x;
        RunningTime = 0.f;
        if (Frame.x > MaxFrames.x) 
        {
            Frame.x = 0;
        }
    }
}

void Sprite::InverseTick(float DeltaTime)
{
    RunningTime += DeltaTime;
    if (RunningTime >= UpdateTime)
    {
        PreviousFrame = Frame.x;
        --Frame.x;
        RunningTime = 0.f;
        if (Frame.x < 0.f)
        {
            Frame.x = MaxFrames.x;
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