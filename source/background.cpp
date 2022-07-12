#include "background.hpp"

Background::Background(const GameTexture& Textures)
    : Textures{Textures} {}

void Background::Tick(float DeltaTime)
{
    // Control the speed at which the background moves based on acceleration or decceleration
    if (IsKeyDown(KEY_W)) {
        if (Speed < 2.f) Speed += 0.01f;
    }
    if (IsKeyUp(KEY_W)) {
        if (Speed > 1.f) Speed -= 0.01f;
    }
    if (IsKeyDown(KEY_S)) {
        if (Speed > 0.5f) Speed -= 0.01f;
    }
    if (IsKeyUp(KEY_S)) {
        if (Speed < 1.f) Speed += 0.01f;
    }
    
    // Update position of wallpaper
    RunningTime += DeltaTime;
    if (RunningTime > UpdateTime) {
        ScreenPos.y += Speed;
    }

    // Reset Background image position
    if (ScreenPos.y >= 0.f) {
        ScreenPos.y = -(5120);
        // ScreenPos.y = -(scale * (Window::Dimension.y + (Window::Dimension.y * 0.6f)));
        // ScreenPos.y = -(scale * (Window::Dimension.y + 432.f));
    }
}

void Background::Draw()
{
    Rectangle Source {0.f,0.f, static_cast<float>(Textures.SpaceBackground.width), static_cast<float>(Textures.SpaceBackground.height)};
    Rectangle Destination {ScreenPos.x, ScreenPos.y, Scale * Textures.SpaceBackground.width, Scale * Textures.SpaceBackground.height};
    DrawTexturePro(Textures.SpaceBackground, Source, Destination, Vector2{}, 0.f, GRAY);
}