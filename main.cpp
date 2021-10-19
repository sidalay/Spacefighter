#include "raylib.h"
#include "ship.h"
#include "background.h"
#include "window.h"

// Vector2 Window {1280,720};
Vector2 Window::Dimension {1280,720};

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Window::Dimension.x, Window::Dimension.y, "Space Invaders");
    SetExitKey(0);
    SetTargetFPS(144);

    Ship Spaceship{};

    Texture2D SpaceBG {LoadTexture("sprites/SpaceBackground-1.png")};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (IsWindowResized()) {
            Window::Dimension.x = GetScreenWidth();
            Window::Dimension.y = GetScreenHeight();
        }

        Background::DrawBackground(SpaceBG);
        float DeltaTime {GetFrameTime()};

        Background::Tick(DeltaTime);
        Spaceship.tick(DeltaTime);

        EndDrawing();
    }

    CloseWindow();
}

