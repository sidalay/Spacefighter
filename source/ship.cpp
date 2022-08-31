#include "ship.hpp"
#include <iostream>

Ship::Ship(const GameTexture& Textures, 
           const GameAudio& Audio, 
           const Randomizer& RandomEngine,
           Projectile& Projectiles,
           const raylib::Window& Window,
           const Shipcolor ShipShade)
    : Stats{Textures, 
            Audio, 
            RandomEngine, 
            Projectiles, 
            Window, 
            raylib::Vector2{static_cast<float>(Window.GetWidth()/2), static_cast<float>(Window.GetHeight()/2)}}, 
      Shade{ShipShade}
{
    switch (Shade)
    {
        case Shipcolor::Purple:
        {
            Sprites.emplace_back(Textures.Accelerate, "Accelerate", raylib::Vector2I{8, 7});
            Sprites.emplace_back(Textures.Decelerate, "Decelerate", raylib::Vector2I{8, 7});
            Sprites.emplace_back(Textures.Normal, "Normal", raylib::Vector2I{8, 7});
            Sprites.emplace_back(Textures.Death, "Death", raylib::Vector2I{8, 3});
            Sprites.emplace_back(Textures.Roll, "Roll", raylib::Vector2I{11, 1}, .7f/11.f);
            break;
        }
        default:
            break;
    }
    Stats.Health = 3.f;
}

void Ship::Tick(float DeltaTime)
{   
    CheckInput();
    CheckAttack();
    Movement(); 
    SetDirectionSprite();
    SetSpriteIndex();
    SpriteTick(DeltaTime);
    CheckDying(DeltaTime);
    ApplyDamage(DeltaTime);
}

void Ship::Draw()
{
    if (Stats.Dying || !Stats.Alive)
    {
        DrawTexturePro(
            Sprites.at(3).GetTexture(), 
            Sprites.at(3).GetSourceRec(), 
            Sprites.at(3).GetPosRec(Stats.ScreenPos, Stats.Scale), 
            raylib::Vector2{}, 0.f, WHITE
        );    
    }
    else if (Stats.Alive) 
    {
        if (Stats.TakingDamage)
        {
            DrawTexturePro(
                Sprites.at(SpriteIndex).GetTexture(), 
                Sprites.at(SpriteIndex).GetSourceRec(), 
                Sprites.at(SpriteIndex).GetPosRec(Stats.ScreenPos, Stats.Scale), 
                raylib::Vector2{}, 0.f, RED
            );    
        }
        else if (Rolling)
        {
            DrawTexturePro(
                Sprites.at(4).GetTexture(), 
                Sprites.at(4).GetSourceRec(), 
                Sprites.at(4).GetPosRec(Stats.ScreenPos, Stats.Scale), 
                raylib::Vector2{}, 0.f, WHITE
            );  
        }
        else if (!Stats.TakingDamage)
        {
            DrawTexturePro(
                Sprites.at(SpriteIndex).GetTexture(), 
                Sprites.at(SpriteIndex).GetSourceRec(), 
                Sprites.at(SpriteIndex).GetPosRec(Stats.ScreenPos, Stats.Scale), 
                raylib::Vector2{}, 0.f, WHITE
            );
        }
    }
}

void Ship::SpriteTick(float DeltaTime)
{
    for (auto& Sprite:Sprites) 
    {
        if (Stats.Dying && Sprite.GetName() == "Death")
        {
            Sprites.at(4).Frame.x = 0;
            Sprite.Tick(DeltaTime);
        }
        else if (Rolling && Sprite.GetName() == "Roll")
        {
            Sprite.Tick(DeltaTime);
        }
        else if (!Rolling && !Stats.Dying)
        {
            Sprites.at(4).Frame.x = 0;
            Sprite.Tick(DeltaTime);
        }
    }
}

void Ship::Movement()
{
    CheckAccel();
    CheckOffScreen();
    CheckDecel();
    CheckRolling();
    UpdateScreenPos();
}

void Ship::CheckAccel()
{
    if (Stats.Alive && !Stats.Dying)
    {
        if (IsKeyDown(KEY_W) && Stats.Speed.y > -Stats.MaxSpeed) 
        {
            Stats.Speed.y += -Accelerate;
        }
        if ((IsKeyDown(KEY_A) || IsKeyPressed(KEY_A)) && Stats.Speed.x > -Stats.MaxSpeed)
        {
            Stats.Speed.x += -Accelerate;
        }
        if ((IsKeyDown(KEY_D) || IsKeyPressed(KEY_D)) && Stats.Speed.x < Stats.MaxSpeed)
        {
            Stats.Speed.x += Accelerate;
        }
        if (IsKeyDown(KEY_S) && Stats.Speed.y < Stats.BrakeSpeed)
        {
            Stats.Speed.y += Accelerate;
        }
    }
}

void Ship::CheckDecel()
{
    if (IsKeyUp(KEY_W) && Stats.Speed.y < 0.f)
    {
        Stats.Speed.y += Decelerate;
    }
    if (IsKeyUp(KEY_A) && Stats.Speed.x < 0.f)
    {
        Stats.Speed.x += Decelerate;
    }    
    if (IsKeyUp(KEY_S) && Stats.Speed.y > 0.f)
    {
        Stats.Speed.y -= Decelerate;
    }
    if (IsKeyUp(KEY_D) && Stats.Speed.x > 0.f)
    {
        Stats.Speed.x -= Decelerate;
    }
}

void Ship::CheckInput()
{
    bool TurningLeft{Heading == Direction::LEFT || Heading == Direction::SUBTLELEFT};
    bool TurningRight{Heading == Direction::RIGHT || Heading == Direction::SUBTLERIGHT};
    bool Turning{TurningLeft || TurningRight};
    bool TurnLeftRelease{
        (IsKeyUp(KEY_A) && TurningLeft) ||
        (IsKeyUp(KEY_A) && IsKeyDown(KEY_W) && (TurningLeft && Heading == Direction::UP)) ||
        (IsKeyUp(KEY_A) && IsKeyDown(KEY_S) && (TurningLeft && Heading == Direction::DOWN))
    };
    bool TurnRightRelease{
        (IsKeyUp(KEY_D) && TurningRight) ||
        (IsKeyUp(KEY_D) && IsKeyDown(KEY_W) && (TurningRight && Heading == Direction::UP)) ||
        (IsKeyUp(KEY_D) && IsKeyDown(KEY_S) && (TurningRight && Heading == Direction::DOWN))
    };

    float MaxTurningTime{1.f/11.f};

    if (IsKeyDown(KEY_W)) 
    {
        State = Shipstate::ACCELERATE;
        Heading = Direction::UP;
    }
    if (IsKeyDown(KEY_S)) 
    {
        State = Shipstate::DECELERATE;
        Heading = Direction::DOWN;
    }

    if (IsKeyDown(KEY_A)) 
    {
        TurnInTime += GetFrameTime();
        Turning = true;

        if (TurnInTime <= MaxTurningTime) 
        {
            Heading = Direction::SUBTLELEFT;
        }
        else 
        {
            Heading = Direction::LEFT;
        }
    }

    if (IsKeyDown(KEY_D)) 
    {
        TurnInTime += GetFrameTime();
        Turning = true;

        if (TurnInTime <= MaxTurningTime) 
        {
            Heading = Direction::SUBTLERIGHT;
        }
        else 
        {
            Heading = Direction::RIGHT;
        }
    }

    if (TurnLeftRelease)
    {
        TurnOutTime += GetFrameTime();
        
        if (TurnOutTime <= MaxTurningTime) 
        {
            Heading = Direction::SUBTLELEFT;
        }
        else 
        {
            Turning = false;
            TurnInTime = 0.f;
            TurnOutTime = 0.f;
            Heading = Direction::NORMAL;
        }
    }
    if (TurnRightRelease)
    {
        TurnOutTime += GetFrameTime();
        
        if (TurnOutTime <= MaxTurningTime) 
        {
            Heading = Direction::SUBTLERIGHT;
        }
        else 
        {
            Turning = false;
            TurnInTime = 0.f;
            TurnOutTime = 0.f;
            Heading = Direction::NORMAL;
        }
    }

    if (IsKeyPressed(KEY_LEFT_SHIFT) && RollReleased)
    {
        Rolling = true;
        RollReleased = false;
    }
    
    if (IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && IsKeyUp(KEY_LEFT_SHIFT) && !Turning)
    {
        State = Shipstate::NORMAL;
        Heading = Direction::NORMAL;
        TurnInTime = 0.f;
        TurnOutTime = 0.f;
    }
}

void Ship::CheckAttack()
{
    if (Stats.Alive && !Stats.Dying && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
    {
        Stats.Projectiles.Load(GetCenterPos(), false);
    }
}

void Ship::CheckRolling()
{   
    // When barrel roll becomes available again
    if (RollTimer >= RollCDTime)
    {
        RollReleased = true;
        RollTimer = 0.f;
    }
    // When barrel roll ends
    else if ((RollTimer >= MaxRollTime) && (RollTimer < RollCDTime))
    {
        RollTimer += GetFrameTime();
        Rolling = false;
        Stats.CollisionOn = true;
    }
    else if (Rolling)
    {
        RollTimer += GetFrameTime();
        Stats.CollisionOn = false;
    }
}

void Ship::CheckDying(float DeltaTime)
{
    if (Stats.Dying)
    {
        Stats.RunningTime += DeltaTime;
        if (Stats.RunningTime >= 0.55f)
        {
            Stats.Alive = false;
            Stats.RunningTime = 0.f;
            Sprites.at(3).Frame.y = 1;
        }
    }
}

void Ship::CheckOffScreen()
{
    float TextureWidth{static_cast<float>(Sprites.at(SpriteIndex).GetTextureWidth(Stats.Scale))};
    float TextureHeight{static_cast<float>(Sprites.at(SpriteIndex).GetTextureHeight(Stats.Scale))};

    if (Stats.ScreenPos.x + TextureWidth < 0) 
    {
        Stats.ScreenPos.x = static_cast<float>(Stats.Window.GetWidth());
    }
    if (Stats.ScreenPos.x > static_cast<float>(Stats.Window.GetWidth())) 
    {
        Stats.ScreenPos.x = 0 - TextureWidth;
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

void Ship::SetDirectionSprite()
{
    switch (Heading)
    {
        case Direction::UP: 
        case Direction::DOWN: 
        case Direction::NORMAL:
            Sprites.at(SpriteIndex).Frame.y = 0;
            break;
        case Direction::LEFT: 
            Sprites.at(SpriteIndex).Frame.y = 2;
            break;
        case Direction::RIGHT:
            Sprites.at(SpriteIndex).Frame.y = 5;
            break;
        case Direction::SUBTLELEFT:
            Sprites.at(SpriteIndex).Frame.y = 1;
            break;
        case Direction::SUBTLERIGHT:
            Sprites.at(SpriteIndex).Frame.y = 4;
            break;
    }
}

void Ship::SetSpriteIndex()
{
    switch (State)
    {
        case Shipstate::ACCELERATE:
            SpriteIndex = static_cast<int>(Shipstate::ACCELERATE);
            break;
        case Shipstate::DECELERATE:
            SpriteIndex = static_cast<int>(Shipstate::DECELERATE);
            break;
        case Shipstate::NORMAL:
            SpriteIndex = static_cast<int>(Shipstate::NORMAL);
            break;
        case Shipstate::ROLL:
            SpriteIndex = static_cast<int>(Shipstate::NORMAL);
            break;
    }
}

void Ship::UpdateScreenPos()
{
    Stats.ScreenPos = Stats.ScreenPos.Add(Stats.Speed);
}

void Ship::TakeDamage()
{
    if (Stats.CollisionOn)
    {
        if (Stats.Health > 1)
        {
            Stats.TakingDamage = true;
        }
        else 
        {
            Stats.Dying = true;
        }
    }
}

void Ship::ApplyDamage(float DeltaTime)
{
    if (Stats.TakingDamage)
    {
        Stats.RunningTime += DeltaTime;
        if (Stats.RunningTime >= 0.55f)
        {
            Stats.Health -= 1.f;
            Stats.RunningTime = 0.f;
            Stats.TakingDamage = false;
        }
    }
}

const raylib::Vector2 Ship::GetCenterPos()
{
    return raylib::Vector2{Stats.ScreenPos.x + (Sprites.at(SpriteIndex).GetTextureWidth(Stats.Scale) * 0.4f), Stats.ScreenPos.y};
}

const raylib::Rectangle Ship::GetCollision() const
{
    float ShipWidth{static_cast<float>(Sprites.at(SpriteIndex).GetTextureWidth(Stats.Scale))};
    float ShipHeight{static_cast<float>(Sprites.at(SpriteIndex).GetTextureHeight(Stats.Scale))};

    return raylib::Rectangle
    {
        Stats.ScreenPos.x + ((ShipWidth * 0.25f)),
        Stats.ScreenPos.y + ((ShipHeight * 0.15f)),
        (ShipWidth - ShipWidth * 0.5f),
        (ShipHeight - ShipHeight * 0.45f),
    };
}
