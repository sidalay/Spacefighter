#include <raylib.h>
#include <raylib-cpp.hpp>
#include "ship.hpp"
#include "background.hpp"
#include "window.hpp"


// extern window dimensions
Vector2 Window::Dimension {1920,1080};
Vector2 Window::PreviousDimension {};

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(Window::Dimension.x, Window::Dimension.y, "Space Invaders");
    SetExitKey(0);
    SetTargetFPS(144);

    Ship Spaceship{};

    Texture2D SpaceBG {LoadTexture("sprites/SpaceBG.png")};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsWindowResized()) {
            Window::Dimension.x = GetScreenWidth();
            Window::Dimension.y = GetScreenHeight();
        }

        float DeltaTime {GetFrameTime()};

        Background::DrawBackground(SpaceBG);
        Background::Tick(DeltaTime);
        Spaceship.tick(DeltaTime);

        EndDrawing();
    }
    
    CloseWindow();
}

