#include "developertools.hpp"

void DeveloperTools::Tick()
{
    if (IsKeyPressed(KEY_GRAVE)) 
    {
        DevToolsOn = !DevToolsOn;
    }

    if (DevToolsOn) 
    {
        if (IsKeyPressed(KEY_ONE)) 
        {
            NoClipOn = !NoClipOn;
        }
        else if (IsKeyPressed(KEY_TWO)) 
        {
            DrawRectanglesOn = !DrawRectanglesOn;
        }
        else if (IsKeyPressed(KEY_THREE)) 
        {
            ShowFPS = !ShowFPS;
        }
        else if (IsKeyPressed(KEY_FOUR)) 
        {
            ShowPos = !ShowPos;
        }
        else if (IsKeyPressed(KEY_FIVE)) 
        {
            ShowSpeed = !ShowSpeed;
        }
        else if (IsKeyPressed(KEY_ZERO)) 
        {
            ShowDevTools = !ShowDevTools;
        }
        else if (IsKeyPressed(KEY_EQUAL)) 
        {

        }
        else if (IsKeyPressed(KEY_MINUS)) 
        {

        }
    }
    else 
    {
        if (NoClipOn) 
        {

        }
            
        ShowPos = false;
        ShowFPS = false;
        NoClipOn = false;
        ShowDevTools = true;
        DrawRectanglesOn = false;
    }
}

void DeveloperTools::DrawTools(const Ship& Spacefighter)
{
    if (DevToolsOn) 
    {
        if (ShowPos) 
        {
            DrawScreenPos(Spacefighter);
        }

        if (ShowFPS) 
        {
            DrawRectangle(15, 215, 90, 30, Color{0,0,0,170});
            DrawFPS(20, 221);
        }

        if (ShowSpeed)
        {
            DrawShipSpeed(Spacefighter);
        }

        if (DrawRectanglesOn)
        {
            DrawCollision(Spacefighter);
        }
        
        if (ShowDevTools) 
        {
            DrawRectangle(15, 270, 220, 25, Color{0,0,0,170});
            DrawText("   Dev Tools Menu", 20, 273, 20, WHITE);
            DrawRectangle(15, 300, 220, 260, Color{0,0,0,170});
            DrawText("  ---- Toggles ----", 20, 310, 20, WHITE);
            DrawText("[`] Dev Tools", 20, 335, 20, !DevToolsOn ? WHITE : LIME);
            DrawText("[1] Noclip", 20, 355, 20, !NoClipOn ? WHITE : LIME);
            DrawText("[2] Collision", 20, 375, 20, !DrawRectanglesOn ? WHITE : LIME);
            DrawText("[3] FPS", 20, 395, 20, !ShowFPS ? WHITE : LIME);
            DrawText("[4] Position", 20, 415, 20, !ShowPos ? WHITE : LIME);
            DrawText("[5] Speed", 20, 435, 20, !ShowSpeed ? WHITE : LIME);
            DrawText("[0] Tools Menu", 20, 455, 20, !IsKeyDown(KEY_ZERO) ? WHITE : LIME);
            DrawText("    ---- Misc ----", 20, 480, 20, WHITE);
            DrawText("[-] Decrease HP", 20, 505, 20, !IsKeyDown(KEY_MINUS) ? WHITE : LIME);
            DrawText("[+] Increase HP", 20, 525, 20, !IsKeyDown(KEY_EQUAL) ? WHITE : LIME);
        }
    }
}

void DeveloperTools::DrawScreenPos(const Ship& Spacefighter)
{
    DrawRectangle(15, 145, 150, 50, Color{0,0,0,170});
    DrawText(TextFormat("Pos.x: %i", static_cast<int>(Spacefighter.GetPos().x)), 20, 150, 20, WHITE);
    DrawText(TextFormat("Pos.y: %i", static_cast<int>(Spacefighter.GetPos().y)), 20, 170, 20, WHITE);
}

void DeveloperTools::DrawShipSpeed(const Ship& Spacefighter)
{
    DrawText(TextFormat("SpeedX: %i", static_cast<int>(Spacefighter.GetSpeed().x)), 20, Row*5, 20, LIME);
    DrawText(TextFormat("SpeedY: %i", static_cast<int>(Spacefighter.GetSpeed().y)), 20, Row*6, 20, LIME);
}

void DeveloperTools::DrawCollision(const Ship& Spacefighter)
{
    DrawRectangle(
        Spacefighter.GetCollision().GetX(),
        Spacefighter.GetCollision().GetY(),
        Spacefighter.GetCollision().GetWidth(),
        Spacefighter.GetCollision().GetHeight(),
        Color{0, 121, 241, 150}
    );
}