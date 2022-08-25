#include "game.hpp"

void Game::Run()
{
    Game::Device Device{};
    Game::Initialize(Device);
    Game::Info Info{};
    Game::Asset Asset{};
    Game::Object Object{
        Projectile{Asset.Textures, Device.Window},
        Ship{Asset.Textures, Asset.Audio, Asset.RandomEngine, Object.Projectiles, Device.Window, Shipcolor::Purple},
        Mothership{Asset.Textures, Asset.Audio, Asset.RandomEngine, Object.Projectiles, Device.Window, Info.Level, Object.Spacefighter}, 
        Background{Asset.Textures}, 
        DeveloperTools{}
    };
    Game::Loop(Info, Device, Object, Asset);
}

void Game::Initialize(Device& Device)
{
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    Device.Window.Init(Device.Screen.x, Device.Screen.y, "Spacefighter");
    Device.Window.SetTargetFPS(144);
    SetExitKey(0);
    HideCursor();
    // Device.Audio.Init();
    // Device.Audio.SetVolume(0.2f);
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
            Object.Projectiles.Tick(Info.DeltaTime);
            Object.Spacefighter.Tick(Info.DeltaTime);
            Object.Mothership.Tick(Info.DeltaTime);
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

void Game::Draw(const Info& Info, Device& Device, Object& Object, const Asset& Asset)
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
            Object.Projectiles.Draw();
            Object.Mothership.Draw();
            Object.Spacefighter.Draw();
            Object.DevTools.DrawTools(Object.Spacefighter, Object.Projectiles, Object.Mothership);
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

