#ifndef GAME_HPP
#define GAME_HPP

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
        
    };

    struct Objects
    {

    };

    void Run();
    void Initialize();
    void CheckScreenSizing();
    void Loop();
    void Tick();
}

#endif // GAME_HPP