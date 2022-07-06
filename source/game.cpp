#include "game.hpp"

void Game::Run()
{
    Game::Info Info{};
    Game::Asset Asset{};
    Game::Object Object{};
    Game::Initialize(Object);
    Game::Loop(Info, Object, Asset);
}

void Game::Initialize(Game::Object& Object)
{
    Object.Window.Init(Object.Screen.x, Object.Screen.y, "Spacefighter");
    Object.Window.SetTargetFPS(144);
    Object.Audio.Init();
    Object.Audio.SetVolume(0.2f);
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetExitKey(0);
    HideCursor();
}

void Game::Loop(Info& Info, Object& Object, const Asset& Asset)
{
    while (!Object.Window.ShouldClose()) 
    {
        Game::Tick(Info, Object, Asset);
    }
}

void Game::Tick(Info& Info, Object& Object, const Asset& Asset)
{
    Game::CheckScreenSizing(Object);
    Game::Draw(Info, Object, Asset);
}

void Game::Draw(Info& Info, Object& Object, const Asset& Asset)
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

void Game::ObjectInit(Object& Object, const Asset& Asset)
{
    
} 
