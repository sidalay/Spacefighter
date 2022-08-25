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
    void Load(const raylib::Vector2 Pos);
    void SetCollided(int Index) {Positions.at(Index).second = true;}
    std::vector<std::pair<raylib::Vector2, bool>> GetPositions() const {return Positions;}
    std::vector<raylib::Circle> GetCollision() const;
private:
    const GameTexture& Textures;
    const raylib::Window& Window;
    Sprite Bullet;
    float Scale{2.5f};
    std::vector<std::pair<raylib::Vector2, bool>> Positions{};
    void SpriteTick(float DeltaTime);
    bool WithinScreen(raylib::Vector2 BulletPos);
    void Unload();
    void Shooting();
};

#endif // PROJECTILE_HPP