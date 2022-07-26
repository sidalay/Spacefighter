#include "enemy.hpp"

Enemy::Enemy(const GameTexture& Textures,
             const GameAudio& Audio,
             const Randomizer& RandomEngine,
             Projectile& Projectiles,
             const raylib::Window& Window,
             MonsterType Monster)
    : Stats{Textures, 
            Audio, 
            RandomEngine, 
            Projectiles, 
            Window,
            raylib::Vector2{static_cast<float>(Window.GetWidth()/2), static_cast<float>(Window.GetHeight()/2)}},
      Monster{Monster}
{
    Sprites.emplace_back(Sprite{Textures.Aliens, raylib::Vector2I{8, 8}});

    switch (Monster)
    {
        case MonsterType::Aqua:
        {
            Sprites.at(SpriteIndex).Frame.y = 0;
            break;
        }
        case MonsterType::Blue:
        {
            Sprites.at(SpriteIndex).Frame.y = 1;
            break;
        }
        case MonsterType::Green:
        {
            Sprites.at(SpriteIndex).Frame.y = 2;
            break;
        }
        case MonsterType::Orange:
        {
            Sprites.at(SpriteIndex).Frame.y = 3;
            break;
        }
        case MonsterType::Pink:
        {
            Sprites.at(SpriteIndex).Frame.y = 4;
            break;
        }
        case MonsterType::Purple:
        {
            Sprites.at(SpriteIndex).Frame.y = 5;
            break;
        }
        case MonsterType::Red:
        {
            Sprites.at(SpriteIndex).Frame.y = 6;
            break;
        }
        case MonsterType::Yellow:
        {
            Sprites.at(SpriteIndex).Frame.y = 7;
            break;
        }
    }
}