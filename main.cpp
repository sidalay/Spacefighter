#include "raylib.h"
#include "ship.h"

int main() {

    Vector2 Window {1280, 720};
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Window.x, Window.y, "Space Invaders");
    SetExitKey(0);
    SetTargetFPS(60);
    
    Ship Spaceship{};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        float DeltaTime {GetFrameTime()};

        Spaceship.tick(DeltaTime);

        EndDrawing();
    }

    CloseWindow();
}