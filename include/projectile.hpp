#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <vector>
#include "sprite.hpp"

class Projectile
{
public:
    Projectile(const GameTexture& Textures, const raylib::Window& Window);
    void Tick(float DeltaTime);
    void Draw();
    void Load(const raylib::Vector2 Pos);
    std::vector<raylib::Circle> GetCollision() const;
private:
    const GameTexture& Textures;
    const raylib::Window& Window;
    Sprite Bullet;
    float Scale{2.5f};
    std::vector<raylib::Vector2> Positions{};

    void SpriteTick(float DeltaTime);
    bool WithinScreen(raylib::Vector2 BulletPos);
};

#endif // PROJECTILE_HPP