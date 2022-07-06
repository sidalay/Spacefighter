#ifndef GAME_HPP
#define GAME_HPP

#include <raylib-cpp.hpp>
#include <textures.hpp>
#include <audio.hpp>

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
        raylib::Vector2I Screen{1920,1080};
        raylib::Window Window;
        raylib::AudioDevice Audio;
    };

    void Run();
    void Initialize(Object& Object);
    void Loop(Info& Info, Asset& Asset, Object& Object);
    void Tick(Info& Info, Asset& Asset, Object& Object);
    void Draw(Info& Info, Asset& Asset, Object& Object);
    void CheckScreenSizing(Object& Object);
};

#endif // GAME_HPP