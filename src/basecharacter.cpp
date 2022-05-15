#include "headers/basecharacter.hpp"

BaseCharacter::BaseCharacter() {}

void BaseCharacter::tick(float deltaTime) 
{
    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        previousFrame = currentFrame;
        ++currentFrame;
        runningTime = 0.f;
        if (currentFrame > maxFrames) currentFrame = 0;
    }
}