#include <raylib.h>
#include "ship.hpp"
#include "background.hpp"
#include "window.hpp"

void SetFullScreen();

// extern window dimensions
Vector2 Window::Dimension {1920,1080};
Vector2 Window::PreviousDimension {};

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
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

        float DeltaTime {GetFrameTime()};

        Background::DrawBackground(SpaceBG);
        Background::Tick(DeltaTime);
        Spaceship.tick(DeltaTime);

        // check for alt + enter
 		if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
 		{
            SetFullScreen();
 		}

        EndDrawing();
    }
    
    CloseWindow();
}

void SetFullScreen()
{
    // see what display we are on right now
    // int display = GetCurrentMonitor();

    if (IsWindowFullscreen()) 
    {
        // if we are full screen, then go back to the windowed size
        ToggleFullscreen();             
        // SetWindowSize(Window.x, Window.y); 
    }
    else
    {                                        
        // if we are not full screen, set the window size to match the monitor we are on
        // SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
        // Window.x = GetMonitorWidth(display);
        // Window.y = GetMonitorHeight(display);
        ToggleFullscreen();
    }
}

