#include "projectile.hpp"

Projectile::Projectile(const GameTexture& Textures, const raylib::Window& Window) 
    : Textures{Textures}, Window{Window}, Bullet{Textures.Projectiles, raylib::Vector2I{8,1}} {}

void Projectile::Tick(float DeltaTime)
{
    SpriteTick(DeltaTime);

    for (auto it = Positions.begin(); it != Positions.end(); ++it)
    {
        if (WithinScreen(*it) || !Collided)
        {
            (*it).y -= 4.f;
        }
        else 
        {
            Positions.erase(it);
            --it;
        }
    }
}

void Projectile::Draw()
{
    for (auto& Pos:Positions)
    {
        DrawTexturePro(Bullet.GetTexture(), Bullet.GetSourceRec(), Bullet.GetPosRec(Pos, Scale), raylib::Vector2{}, 0.f, WHITE);
    }
}

void Projectile::Load(const raylib::Vector2 Pos)
{
    Positions.push_back(Pos);
}

void Projectile::SpriteTick(float DeltaTime)
{
    Bullet.Tick(DeltaTime);
}

bool Projectile::WithinScreen(raylib::Vector2 BulletPos)
{
    float TextureWidth{static_cast<float>(Bullet.GetTextureWidth(Scale))};
    float TextureHeight{static_cast<float>(Bullet.GetTextureHeight(Scale))};

    for (auto& Pos:Positions)
    {
        if (Pos == BulletPos && 
           (Pos.x + TextureWidth < 0 || 
            Pos.x > static_cast<float>(Window.GetWidth()) ||
            Pos.y < 0 ||
            Pos.y >= static_cast<float>(Window.GetHeight()) - TextureHeight)) 
        {
            return false;
        }
    }
    return true;
}

std::vector<raylib::Circle> Projectile::GetCollision() const
{
    int Width{Bullet.GetTextureWidth(Scale)};
    int Height{Bullet.GetTextureHeight(Scale)};
    float Radius{6.5f};
    std::vector<raylib::Circle> Collisions{};

    for (auto& Pos:Positions)
    {
        Collisions.push_back(
            raylib::Circle
            {
                static_cast<int>(Pos.x) + ((Width/2)),
                static_cast<int>(Pos.y) + ((Height/2)),
                Radius
            }    
        ); 
    }

    return Collisions;
}