#include "basestats.hpp"

BaseStats::BaseStats(const GameTexture& Textures,
                     const GameAudio& Audio,
                     const Randomizer& RandomEngine,
                     Projectile& Projectiles,
                     const raylib::Window& Window,
                     const raylib::Vector2 ScreenPos)
    : Textures{Textures}, 
      Audio{Audio}, 
      RandomEngine{RandomEngine}, 
      Projectiles{Projectiles}, 
      Window{Window}, 
      ScreenPos{ScreenPos} {};

BaseStats& BaseStats::operator=(BaseStats&& Rhs)
{
    if (this == &Rhs)
    {
        return *this;
    }  
}