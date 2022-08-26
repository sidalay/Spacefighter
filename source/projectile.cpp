#include "projectile.hpp"

Projectile::Projectile(const GameTexture& Textures, const raylib::Window& Window) 
    : Textures{Textures}, 
      Window{Window}, 
      Bullet{Textures.Projectiles, 
      raylib::Vector2I{8,1}} {}

Projectile::Projectile(Projectile&& Object)
    : Textures{std::move(Object.Textures)},
      Window{std::move(Object.Window)},
      Bullet{std::move(Object.Bullet)},
      Scale{std::move(Object.Scale)},
      ShipPos{std::move(Object.ShipPos)},
      ShipAtkPos{std::move(Object.ShipAtkPos)},
      EnemyAtkPos{std::move(Object.EnemyAtkPos)} {}

Projectile& Projectile::operator=(Projectile&& Object)
{
    if (this == &Object)
    {
        return *this;
    }

    this->Bullet = std::move(Object.Bullet);
    this->Scale = std::move(Object.Scale);
    this->ShipPos = std::move(Object.ShipPos);
    this->ShipAtkPos = std::move(Object.ShipAtkPos);
    this->EnemyAtkPos = std::move(Object.EnemyAtkPos);

    return *this;
}

void Projectile::Tick(float DeltaTime)
{
    SpriteTick(DeltaTime);
    Shooting();
    Unload();
}

void Projectile::Draw()
{
    for (auto& Pos:ShipAtkPos)
    {
        if (!Pos.second) 
        {
            DrawTexturePro(Bullet.GetTexture(), Bullet.GetSourceRec(), Bullet.GetPosRec(Pos.first, Scale), raylib::Vector2{}, 0.f, WHITE);
        }
    }

    for (auto& EnemyPos:EnemyAtkPos)
    {
        if (!EnemyPos.second)
        {
            DrawTexturePro(Bullet.GetTexture(), Bullet.GetSourceRec(), Bullet.GetPosRec(EnemyPos.first, Scale), raylib::Vector2{}, 0.f, WHITE);
        }
    }
}

void Projectile::Load(const raylib::Vector2 Pos, bool Enemy, raylib::Vector2 SpacefighterPos)
{
    if (Enemy)
    {
        EnemyAtkPos.emplace_back(std::make_pair(Pos, false));
        ShipPos.emplace_back(SpacefighterPos);
    }
    else 
    {
        ShipAtkPos.emplace_back(std::make_pair(Pos, false));
    }
}

void Projectile::Unload()
{
    std::erase_if(ShipAtkPos, [&](auto&& Position) {
        return !WithinScreen(Position.first);
    });

    std::erase_if(EnemyAtkPos, [&](auto&& Position) {
        return !WithinScreen(Position.first);
    });
}

void Projectile::Shooting()
{
    for (auto& Position:ShipAtkPos)
    {
        if (WithinScreen(Position.first))
        {
            Position.first.y -= 4.f;
        }
    }

    // for (auto& EnemyPos:EnemyAtkPos)
    // {
    //     if (WithinScreen(EnemyPos.first))
    //     {
    //         EnemyPos.first.y += 4.f;
    //     }
    // }

    for (int i = 0; i < static_cast<int>(EnemyAtkPos.size()); ++i)
    {
        raylib::Vector2 ToTarget {Vector2Scale(Vector2Normalize(Vector2Subtract(ShipPos.at(i), EnemyAtkPos.at(i).first)), 4.f)};
        if (WithinScreen(EnemyAtkPos.at(i).first))
        {
            EnemyAtkPos.at(i).first = Vector2Add(EnemyAtkPos.at(i).first, Vector2{0.f, 2.f});
        }
    }
}

void Projectile::SpriteTick(float DeltaTime)
{
    Bullet.Tick(DeltaTime);
}

bool Projectile::WithinScreen(raylib::Vector2 BulletPos)
{
    float TextureWidth{static_cast<float>(Bullet.GetTextureWidth(Scale))};
    float TextureHeight{static_cast<float>(Bullet.GetTextureHeight(Scale))};

    for (auto& Pos:ShipAtkPos)
    {
        if (Pos.first == BulletPos && 
           (Pos.first.x + TextureWidth < 0 || 
            Pos.first.x > static_cast<float>(Window.GetWidth()) ||
            Pos.first.y < 0 ||
            Pos.first.y >= static_cast<float>(Window.GetHeight()) - TextureHeight)) 
        {
            return false;
        }
    }
    return true;
}

std::vector<raylib::Circle> Projectile::GetShipAtkCollision() const
{
    int Width{Bullet.GetTextureWidth(Scale)};
    int Height{Bullet.GetTextureHeight(Scale)};
    float Radius{6.5f};
    std::vector<raylib::Circle> Collisions{};

    for (auto& Pos:ShipAtkPos)
    {
        Collisions.push_back(
            raylib::Circle
            {
                static_cast<int>(Pos.first.x) + ((Width/2)),
                static_cast<int>(Pos.first.y) + ((Height/2)),
                Radius
            }    
        ); 
    }

    return Collisions;
}

std::vector<raylib::Circle> Projectile::GetEnemyAtkCollision() const
{
    int Width{Bullet.GetTextureWidth(Scale)};
    int Height{Bullet.GetTextureHeight(Scale)};
    float Radius{6.5f};
    std::vector<raylib::Circle> Collisions{};

    for (auto& EnemyPos:EnemyAtkPos)
    {
        Collisions.push_back(
            raylib::Circle
            {
                static_cast<int>(EnemyPos.first.x) + ((Width/2)),
                static_cast<int>(EnemyPos.first.y) + ((Height/2)),
                Radius
            }    
        ); 
    }

    return Collisions;
}