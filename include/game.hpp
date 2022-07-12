#ifndef GAME_HPP
#define GAME_HPP

#include "ship.hpp"
#include "background.hpp"

namespace Game
{
    enum class State
    {
        START, 
        PAUSED, 
        RUNNING, 
        TRANSITION, 
        EXIT, 
        GAMEOVER
    };

    struct Info
    {
        float DeltaTime{};
        Game::State State{Game::State::RUNNING};
        Game::State PrevState{Game::State::START};
        Game::State NextState{Game::State::RUNNING};
    };

    struct Asset
    {
        GameTexture Textures;
        GameAudio Audio;
    };

    struct Device
    {
        raylib::Vector2I Screen{1920,1080};
        raylib::Window Window;
        raylib::AudioDevice Audio;
    };

    struct Object
    {
        Ship Spacefighter;
        Background Background;
    };

    void Run();
    void Initialize(Device& Device);
    void Loop(Info& Info, Device& Device, Object& Object, const Asset& Asset);
    void Tick(Info& Info, Device& Device, Object& Object, const Asset& Asset);
    void Draw(Info& Info, Device& Device, Object& Object, const Asset& Asset);
    void CheckScreenSizing(Device& Device);
};

#endif // GAME_HPP