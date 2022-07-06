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

    struct Object
    {
        raylib::Vector2I Screen{1920,1080};
        raylib::Window Window;
        raylib::AudioDevice Audio;
        Ship Spacefighter;
    };

    void Run();
    void Initialize(Object& Object);
    void Loop(Info& Info, Object& Object, const Asset& Asset);
    void Tick(Info& Info, Object& Object, const Asset& Asset);
    void Draw(Info& Info, Object& Object, const Asset& Asset);
    void CheckScreenSizing(Object& Object);
    void ObjectInit(Object& Object, const Asset& Asset);
};

#endif // GAME_HPP