#include "game.hpp"

void Game::Run()
{
    Game::Info Info;
    Game::Asset Asset;
    Game::Object Object;
    Game::Initialize(Object);
    Game::Loop(Info, Asset, Object);
}

void Game::Initialize(Game::Object& Object)
{
    Object.Window.Init(Object.Screen.x, Object.Screen.y, "Spacefighter");
    Object.Window.SetTargetFPS(144);
    Object.Audio.Init();
    Object.Audio.SetVolume(0.5f);
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetExitKey(0);
    HideCursor();
}

void Game::Loop(Info& Info, Asset& Asset, Object& Object)
{
    while (!Object.Window.ShouldClose()) 
    {
        Game::Tick(Info, Asset, Object);
    }
}

void Game::Tick(Info& Info, Asset& Asset, Object& Object)
{
    Game::CheckScreenSizing(Object);
    Game::Draw(Info, Asset, Object);
}

void Game::Draw(Info& Info, Asset& Asset, Object& Object)
{
    Object.Window.BeginDrawing();
    Object.Window.ClearBackground(BLACK);

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
}

void Game::CheckScreenSizing(Object& Object)
{
    if (Object.Window.IsResized())
    {
        Object.Screen.x = Object.Window.GetWidth();
        Object.Screen.y = Object.Window.GetHeight();
    }

    if (IsKeyPressed(KEY_ENTER) && ((IsKeyPressed(KEY_RIGHT_ALT) || IsKeyPressed(KEY_LEFT_ALT))))
    {
        Object.Window.ToggleFullscreen();
    }
}

