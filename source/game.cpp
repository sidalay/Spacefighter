#include "game.hpp"

void Game::Run()
{
    Game::Device Device{};
    Game::Initialize(Device);
    Game::Info Info{};
    Game::Asset Asset{};
    Game::Object Object{Ship{Asset.Textures, Asset.Audio, Device.Window, Shipcolor::Purple}, Background{Asset.Textures}};
    Game::Loop(Info, Device, Object, Asset);
}

void Game::Initialize(Device& Device)
{
    Device.Window.Init(Device.Screen.x, Device.Screen.y, "Spacefighter");
    Device.Window.SetTargetFPS(144);
    // Device.Audio.Init();
    // Device.Audio.SetVolume(0.2f);
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetExitKey(0);
    HideCursor();
}

void Game::Loop(Info& Info, Device& Device, Object& Object, const Asset& Asset)
{
    while (!Device.Window.ShouldClose()) 
    {
        Game::Tick(Info, Device, Object, Asset);
        Game::Draw(Info, Device, Object, Asset);
    }
}

void Game::Tick(Info& Info, Device& Device, Object& Object, const Asset& Asset)
{
    Info.DeltaTime = GetFrameTime();
    Game::CheckScreenSizing(Device);

    switch (Info.State)
    {
        case Game::State::START:
        {
            break;
        }
        case Game::State::RUNNING:
        {
            Object.Background.Tick(Info.DeltaTime);
            Object.Spacefighter.Tick(Info.DeltaTime);
            Object.DevTools.Tick();
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
}

void Game::Draw(Info& Info, Device& Device, Object& Object, const Asset& Asset)
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
            Object.Background.Draw();
            Object.Spacefighter.Draw();
            Object.DevTools.DrawTools(Object.Spacefighter);
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

    if (IsKeyDown(KEY_ENTER) && ((IsKeyDown(KEY_RIGHT_ALT) || IsKeyDown(KEY_LEFT_ALT))))
    {
        Device.Window.ToggleFullscreen();
    }
}

