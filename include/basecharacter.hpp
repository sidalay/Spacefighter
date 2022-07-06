#ifndef BASECHARACTER_HPP
#define BASECHARACTER_HPP

#include <raylib-cpp.hpp>
#include <vector>
#include "audio.hpp"
#include "sprite.hpp"
#include "textures.hpp"

class BaseCharacter
{
protected:
    bool Alive{true};
    int CurrentFrame{};
    int PreviousFrame{};
    int MaxFrames{7};
    float UpdateTime{1.f/14.f};
    float RunningTime{};
    float Health {};
    float Speed {4};
    float Width {};
    float Height {};
    float Scale {4.f};

public:
    BaseCharacter();
    // void undoMovement();
    // Rectangle getCollisionRec();
    virtual void Tick(float DeltaTime);
    float GetHealth() const {return Health;}
};

#endif