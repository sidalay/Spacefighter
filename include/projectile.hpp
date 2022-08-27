#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <vector>
#include "sprite.hpp"

class Projectile
{
public:
    Projectile(const GameTexture& Textures, const raylib::Window& Window);
    ~Projectile() = default;
    Projectile(const Projectile&) = default;
    Projectile(Projectile&& Object);
    Projectile& operator=(const Projectile&) = default;
    Projectile& operator=(Projectile&& Object);
    void Tick(float DeltaTime);
    void Draw();
    void Load(const raylib::Vector2 Pos, bool Enemy, raylib::Vector2 SpacefighterPos = {0.f,0.f});
    void SetShipAtkCollided(int Index) {ShipAtkPos.at(Index).second = true;}
    void SetEnemyAtkCollided(int Index) {EnemyAtkPos.at(Index).second = true;}
    std::vector<std::pair<raylib::Vector2, bool>> GetPositions() const {return ShipAtkPos;}
    std::vector<std::pair<raylib::Vector2, bool>> GetEnemyPositions() const {return EnemyAtkPos;}
    std::vector<raylib::Circle> GetShipAtkCollision() const;
    std::vector<raylib::Circle> GetEnemyAtkCollision() const;
private:
    const GameTexture& Textures;
    const raylib::Window& Window;
    Sprite Bullet;
    float Scale{2.5f};
    std::vector<raylib::Vector2> ShipPos{};
    std::vector<std::pair<raylib::Vector2, bool>> ShipAtkPos{};
    std::vector<std::pair<raylib::Vector2, bool>> EnemyAtkPos{};
    void SpriteTick(float DeltaTime);
    bool WithinScreen(raylib::Vector2 BulletPos, std::vector<std::pair<raylib::Vector2, bool>>Container);
    void Unload();
    void Shooting();
};

#endif // PROJECTILE_HPP