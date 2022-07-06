#include <raylib.h>
#include <raylib-cpp.hpp>

int main() {

    Ship Spaceship{};
    Texture2D SpaceBG {LoadTexture("sprites/SpaceBG.png")};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        float DeltaTime {GetFrameTime()};

        Background::DrawBackground(SpaceBG);
        Background::Tick(DeltaTime);
        Spaceship.tick(DeltaTime);

        EndDrawing();
    }
    
    CloseWindow();
}

