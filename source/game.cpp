#include "game.hpp"

void Game::Run()
{
    Game::Device Device{};
    Game::Initialize(Device);
    Game::Info Info{};
    Game::Asset Asset{};
    Game::Loop(Info, Device, Asset);
}

void Game::Initialize(Device& Device)
{
    Device.Window.Init(Device.Screen.x, Device.Screen.y, "Spacefighter");
    Device.Window.SetTargetFPS(144);
    Device.Audio.Init();
    Device.Audio.SetVolume(0.2f);
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetExitKey(0);
    HideCursor();
}

void Game::Loop(Info& Info, Device& Device, const Asset& Asset)
{
    while (!Device.Window.ShouldClose()) 
    {
        Game::Tick(Info, Device, Asset);
    }
}

void Game::Tick(Info& Info, Device& Device, const Asset& Asset)
{
    Game::CheckScreenSizing(Device);
    Game::Draw(Info, Device, Asset);
}

void Game::Draw(Info& Info, Device& Device, const Asset& Asset)
{
    Device.Window.BeginDrawing();
    Device.Window.ClearBackground(BLACK);

    switch (Info.State)
    {
        case Game::State::START:
        {
            break;
        }
        case Game::State::RUNNING:
        {
            break;
        }
        case Game::State::PAUSED:
        {
            break;
        }
        case Game::State::EXIT:
        {
            break;
        }
        case Game::State::GAMEOVER:
        {
            break;
        }
        case Game::State::TRANSITION:
        {
            break;
        }
    }

    Device.Window.EndDrawing();
}

void Game::CheckScreenSizing(Device& Device)
{
    if (Device.Window.IsResized())
    {
        Device.Screen.x = Device.Window.GetWidth();
        Device.Screen.y = Device.Window.GetHeight();
    }

    if (IsKeyPressed(KEY_ENTER) && ((IsKeyPressed(KEY_RIGHT_ALT) || IsKeyPressed(KEY_LEFT_ALT))))
    {
        Device.Window.ToggleFullscreen();
    }
}

