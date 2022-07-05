#include "textures.hpp"

GameTexture::~GameTexture()
{
    UnloadTexture(Aliens);
    UnloadTexture(Accelerate);
    UnloadTexture(Decelerate);
    UnloadTexture(Normal);
    UnloadTexture(Projectiles);
    UnloadTexture(SpaceBackground);
}