#ifndef SHIP_HPP
#define SHIP_HPP

#include "basestats.hpp"

enum class Shipcolor
{
    Red, Purple, Green, Blue
};

enum class Shipstate
{
    ACCELERATE, DECELERATE, NORMAL, ROLL
};

class Ship
{
public:
    Ship(const GameTexture& Textures, 
         const GameAudio& Audio,
         const Randomizer& RandomEngine,
         Projectile& Projectiles,
         const raylib::Window& Window,
         const Shipcolor ShipShade = Shipcolor::Purple);
    void Tick(float DeltaTime);
    void Draw();
    void TakeDamage();
    void SetAlive() {Stats.Alive = true; Stats.Health = 3;}
    const raylib::Vector2& GetPos() const {return Stats.ScreenPos;}
    const raylib::Vector2 GetCenterPos();
    const raylib::Vector2 GetSpeed() const {return Stats.Speed;}
    const raylib::Rectangle GetCollision() const;
private:
    BaseStats Stats;
    Shipcolor Shade{};
    Shipstate State{Shipstate::NORMAL}; 
    Direction Heading{Direction::UP};
    std::vector<Sprite> Sprites{};

    int SpriteIndex{};
    float TurnInTime{};
    float TurnOutTime{};
    float RollTimer{};
    float MaxRollTime{0.7f};
    float RollCDTime{1.f};
    float Accelerate{0.05f};
    float Decelerate{0.03f};
    bool RollLeft{false};
    bool RollRight{false};
    bool Rolling{false};
    bool RollReleased{true};

    void SpriteTick(float DeltaTime);
    void Movement();
    void CheckAccel();
    void CheckDecel();
    void CheckInput();
    void CheckAttack();
    void CheckRolling();
    void CheckDying(float DeltaTime);
    void CheckOffScreen();
    void ApplyDamage(float DeltaTime);
    void SetDirectionSprite();
    void SetSpriteIndex();
    void UpdateScreenPos();
};

#endif