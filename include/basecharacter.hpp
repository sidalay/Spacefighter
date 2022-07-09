#ifndef BASECHARACTER_HPP
#define BASECHARACTER_HPP

#include <vector>
#include "audio.hpp"
#include "sprite.hpp"

enum class Direction
{
    UP, LEFT, DOWN, RIGHT, SUBTLELEFT, SUBTLERIGHT, NORMAL
};

class BaseCharacter
{
protected:
    bool Alive{true};
    float UpdateTime{1.f/14.f};
    float RunningTime{};
    float Health{};
    float Speed{4};
    float Scale{4.f};

public:
    BaseCharacter();
    // void undoMovement();
    // Rectangle getCollisionRec();
    virtual void Tick(float DeltaTime);
    float GetHealth() const {return Health;}
};

#endif