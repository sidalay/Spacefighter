#include "enemy.hpp"

Enemy::Enemy(const GameTexture& Textures,
             const GameAudio& Audio,
             const Randomizer& RandomEngine,
             Projectile& Projectiles,
             const raylib::Window& Window,
             const raylib::Vector2 ScreenPos,
             MonsterType Monster)
    : Stats{Textures, 
            Audio, 
            RandomEngine, 
            Projectiles, 
            Window,
            ScreenPos},
      Monster{Monster}
{
    Sprites.emplace_back(Sprite{Textures.Aliens, raylib::Vector2I{8, 8}});
    SetMonsterSprite();
}

void Enemy::Tick(float DeltaTime)
{
    CheckAttack();
    Movement();
    SetSpriteIndex();
    SpriteTick(DeltaTime);
}

void Enemy::Draw()
{
    DrawTexturePro(
        Sprites.at(SpriteIndex).GetTexture(), 
        Sprites.at(SpriteIndex).GetSourceRec(), 
        Sprites.at(SpriteIndex).GetPosRec(Stats.ScreenPos, Stats.Scale), 
        raylib::Vector2{}, 0.f, WHITE
    );
}

void Enemy::SpriteTick(float DeltaTime)
{
    for (auto& Sprite:Sprites) 
    {
        Sprite.Tick(DeltaTime);
    }
}

void Enemy::Movement()
{
    SwayLeftRight();
    UpdateScreenPos();
}

void Enemy::SwayLeftRight()
{
    // Set up randomizer code to randomize movement
    // This is temporary code
    Stats.Speed.x += Accelerate;
    CheckOffScreen();
}

void Enemy::CheckAttack()
{
    // Set up randomizer code
    // Stats.Projectiles.Load(GetCenterPos());
}

void Enemy::CheckOffScreen()
{
    float TextureWidth{static_cast<float>(Sprites.at(SpriteIndex).GetTextureWidth(Stats.Scale))};
    float TextureHeight{static_cast<float>(Sprites.at(SpriteIndex).GetTextureHeight(Stats.Scale))};

    if (Stats.ScreenPos.x + TextureWidth < 0 || Stats.ScreenPos.x > static_cast<float>(Stats.Window.GetWidth())) 
    {
        Accelerate == !Accelerate;
    }
    if (Stats.ScreenPos.y < 0) 
    {
        Stats.ScreenPos.y = 0;
    }
    if (Stats.ScreenPos.y >= static_cast<float>(Stats.Window.GetHeight()) - TextureHeight) 
    {
        Stats.ScreenPos.y = (static_cast<float>(Stats.Window.GetHeight()) - TextureHeight);
    }
}

void Enemy::SetSpriteIndex()
{

}

void Enemy::SetMonsterSprite()
{
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

void Enemy::UpdateScreenPos()
{
    Stats.ScreenPos = Stats.ScreenPos.Add(Stats.Speed);
}

const raylib::Rectangle Enemy::GetCollision() const
{
    float TextureWidth{static_cast<float>(Sprites.at(SpriteIndex).GetTextureWidth(Stats.Scale))};
    float TextureHeight{static_cast<float>(Sprites.at(SpriteIndex).GetTextureHeight(Stats.Scale))};

    return raylib::Rectangle
    {
        Stats.ScreenPos.x + ((TextureWidth * 0.25f)),
        Stats.ScreenPos.y + ((TextureHeight * 0.15f)),
        (TextureWidth - TextureWidth * 0.5f),
        (TextureHeight - TextureHeight * 0.45f),
    };
}

const raylib::Vector2 Enemy::GetCenterPos()
{
    return raylib::Vector2{Stats.ScreenPos.x + (Sprites.at(SpriteIndex).GetTextureWidth(Stats.Scale) * 0.4f), Stats.ScreenPos.y};
}