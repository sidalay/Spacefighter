#ifndef BASECHARACTER_HPP
#define BASECHARACTER_HPP

#include "raylib.h"

class BaseCharacter
{
protected:
    Texture2D texture{};

    bool alive{true};
    int currentFrame{};
    int previousFrame{};
    int maxFrames{7};
    float updateTime{1.f/14.f};
    float runningTime{};
    float health {};
    float speed {4};
    float width {};
    float height {};
    float scale {4.f};

public:
    BaseCharacter();
    // void undoMovement();
    // Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    float getHealth() const {return health;}
};

#endif