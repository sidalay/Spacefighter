#ifndef GAME_HPP
#define GAME_HPP

#include <raylib-cpp.hpp>
#include "ship.hpp"

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
        Game::State State{Game::State::TRANSITION};
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
        raylib::Vector2I Screen{1280,720};
        raylib::Window Window;
        raylib::AudioDevice Audio;
    };

    void Run();
    void Initialize(Device& Device);
    void Loop(Info& Info, Device& Device, const Asset& Asset);
    void Tick(Info& Info, Device& Device, const Asset& Asset);
    void Draw(Info& Info, Device& Device, const Asset& Asset);
    void CheckScreenSizing(Device& Device);
};

#endif // GAME_HPP