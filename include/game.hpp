#ifndef GAME_HPP
#define GAME_HPP

#include <raylib-cpp.hpp>
#include "audio.hpp"
#include "background.hpp"
#include "ship.hpp"
#include "textures.hpp"

namespace raylib 
{
    struct Vector2I
    {
        int x;
        int y;
    };
};

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
        Ship Spacefighter;
        raylib::Vector2I Screen{1920,1080};
        raylib::Window Window;
        raylib::AudioDevice Audio;
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