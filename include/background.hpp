#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "textures.hpp"

class Background
{
public:
    Background(const GameTexture& Textures);
    ~Background() = default;
    Background(const Background&) = delete;
    Background(Background&&) = default;
    Background& operator=(const Background&) = delete;
    Background& operator=(Background&&) = default;
    void Tick(float DeltaTime);
    void Draw();
private:
    const GameTexture& Textures;
    float Scale{4.f};
    raylib::Vector2 ScreenPos{0.f, -(5120.f)};
    float RunningTime{};
    float UpdateTime{1.f/14.f};
    float Speed{1.f};
    

    // Vector2 ScreenPos{0.f, -(scale * Window::Dimension.y)};
    // Vector2 ScreenPos{0.f, -(scale * (Window::Dimension.y + (Window::Dimension.y * 0.6f)))};
    // Vector2 ScreenPos{0.f, -(scale * (Window::Dimension.y + 432.f))};
};

#endif // BACKGROUND_HPP