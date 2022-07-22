#ifndef GAME_HPP
#define GAME_HPP

#include "developertools.hpp"
#include "background.hpp"

namespace Game
{
    enum class State;
    struct Info;
    struct Device;
    struct Object;
    struct Asset;

    void Run();
    void Initialize(Device& Device);
    void Loop(Info& Info, Device& Device, Object& Object, const Asset& Asset);
    void Tick(Info& Info, Device& Device, Object& Object, const Asset& Asset);
    void Draw(const Info& Info, Device& Device, Object& Object, const Asset& Asset);
    void CheckScreenSizing(Device& Device);

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
    struct Device
    {
        raylib::Vector2I Screen{1920,1080};
        raylib::Window Window;
        raylib::AudioDevice Audio;
    };
    struct Object
    {
        Projectile Projectiles; 
        Ship Spacefighter;
        Background Background;
        DeveloperTools DevTools;
    };
    struct Asset
    {
        GameTexture Textures;
        GameAudio Audio;
        Randomizer RandomEngine;
    };
};

#endif // GAME_HPP