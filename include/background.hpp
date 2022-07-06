#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <raylib.h>
#include <iostream>

namespace Background
{
    float Scale{4.f};
    // Vector2 ScreenPos{0.f, -(scale * Window::Dimension.y)};
    // Vector2 ScreenPos{0.f, -(scale * (Window::Dimension.y + (Window::Dimension.y * 0.6f)))};
    Vector2 ScreenPos{0.f, -(5120.f)};
    // Vector2 ScreenPos{0.f, -(scale * (Window::Dimension.y + 432.f))};
    float RunningTime{};
    float UpdateTime{1.f/14.f};
    float Speed{1.f};

    void Tick(float DeltaTime) {

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
            // ScreenPos.y = -(scale * (Window::Dimension.y + (Window::Dimension.y * 0.6f)));
            ScreenPos.y = -(5120);
            // ScreenPos.y = -(scale * (Window::Dimension.y + 432.f));
        }

        DrawText(TextFormat("ScreenPos.y: %i", static_cast<int>(Background::ScreenPos.y)), 20, 20, 20, RED);
        DrawText(TextFormat("Speed: %i", static_cast<int>(Background::Speed)), 20, 40, 20, BLUE);

    }
    
    // Draw the background
    void DrawBackground(Texture2D BG) {
        Rectangle Source {0.f,0.f, static_cast<float>(BG.width), static_cast<float>(BG.height)};
        Rectangle Destination {ScreenPos.x, ScreenPos.y, Scale * BG.width, Scale * BG.height};
        DrawTexturePro(BG, Source, Destination, Vector2{}, 0.f, GRAY);
    }
}

#endif 