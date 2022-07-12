#include "ship.hpp"

Ship::Ship(const GameTexture& Textures, 
           const GameAudio& Audio, 
           const raylib::Window& Window,
           const Shipcolor Shade)
    : Textures{Textures}, Audio{Audio}, Shade{Shade}, Window{Window}, ScreenPos{raylib::Vector2{static_cast<float>(Window.GetWidth()/2), static_cast<float>(Window.GetHeight()/2)}}
{
    switch (Shade)
    {
        case Shipcolor::Purple:
        {
            Sprites.emplace_back(Sprite{Textures.Accelerate, raylib::Vector2I{8, 7}});
            Sprites.emplace_back(Sprite{Textures.Decelerate, raylib::Vector2I{8, 7}});
            Sprites.emplace_back(Sprite{Textures.Normal, raylib::Vector2I{8, 7}});
            break;
        }
        default:
            break;
    }
}

void Ship::Tick(float DeltaTime)
{   
    Movement(); 
    CheckInput();
    SetDirectionSprite();
    SetSpriteIndex();
    SpriteTick(DeltaTime);
}

void Ship::Draw()
{
    DrawTexturePro(Sprites.at(SpriteIndex).Texture, 
                   Sprites.at(SpriteIndex).GetSourceRec(), 
                   Sprites.at(SpriteIndex).GetPosRec(ScreenPos, Stats.Scale), 
                   raylib::Vector2{}, 0.f, WHITE);

    DrawText(TextFormat("Velocity.x: %i", static_cast<int>(Velocity.x)), 20, 20, 20, BLUE);
    DrawText(TextFormat("Velocity.y: %i", static_cast<int>(Velocity.y)), 20, 40, 20, BLUE);
    DrawText(TextFormat("ScreenPos.x: %i", static_cast<int>(ScreenPos.x)), 20, 60, 20, PURPLE);
    DrawText(TextFormat("ScreenPos.y: %i", static_cast<int>(ScreenPos.y)), 20, 80, 20, PURPLE);
    DrawText(TextFormat("Speed: %i", static_cast<int>(Stats.Speed)), 20, 100, 20, LIME);
    DrawText(TextFormat("Shifting: %i", static_cast<int>(Shifting)), 20, 120, 20, LIME);
}

void Ship::SpriteTick(float DeltaTime)
{
    for (auto& Sprite:Sprites) {
        Sprite.Tick(DeltaTime);
    }
}

void Ship::Movement()
{
    PrevScreenPos = ScreenPos;
    CheckOffScreen();
    CheckSpeed();
    IncreaseVelocity();
    ReduceVelocity();
    ScreenPos = ScreenPos.Add(Velocity.Normalize().Scale(Stats.Speed));
}

void Ship::CheckInput()
{
    PrevHeading = Heading;
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
    
    if (IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && !Turning)
    {
        State = Shipstate::NORMAL;
        Heading = Direction::NORMAL;
        TurnInTime = 0.f;
        TurnOutTime = 0.f;
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
    }
}

void Ship::CheckOffScreen()
{
    float TextureWidth{static_cast<float>(Sprites.at(SpriteIndex).GetTextureWidth())};
    float TextureHeight{static_cast<float>(Sprites.at(SpriteIndex).GetTextureHeight())};

    if (ScreenPos.x + TextureWidth < 0) 
    {
        ScreenPos.x = static_cast<float>(Window.GetWidth());
    }
    if (ScreenPos.x > static_cast<float>(Window.GetWidth())) 
    {
        ScreenPos.x = 0 - TextureWidth;
    }
    if (ScreenPos.y < 0) 
    {
        ScreenPos.y = 0;
    }
    if (ScreenPos.y >= static_cast<float>(Window.GetHeight()) - TextureHeight) 
    {
        ScreenPos.y = (static_cast<float>(Window.GetHeight()) - TextureHeight);
    }
}

void Ship::CheckSpeed()
{
    bool Accelerating{Heading == Direction::UP};
    bool Decelerating{Heading == Direction::DOWN};
    bool TurningLeft{Heading == Direction::LEFT || Heading == Direction::SUBTLELEFT};
    bool TurningRight{Heading == Direction::RIGHT || Heading == Direction::SUBTLERIGHT};
    bool Turning{TurningLeft || TurningRight};

    CheckShifting();

    if (Shifting && Stats.Speed > 3.f)
    {
        Stats.Speed -= Decelerate;
    }
    else if (Shifting && Stats.Speed <= 3.f)
    {
        Shifting = false;
    }
    else if (Turning || Accelerating)
    {
        if (Stats.Speed <= Stats.MaxSpeed) 
        {
            Stats.Speed += Accelerate;
        }
    }
    else if (Decelerating)
    {
        if (Stats.Speed >= Brakespeed)
        {
            Stats.Speed -= 0.01;
        }
    }
    else
    {
        if (Stats.Speed > 0.f)
        {
            Stats.Speed -= Decelerate;
        }
    }
}

void Ship::ReduceVelocity()
{
    float SlowDown{1.f};

    if (State == Shipstate::NORMAL)
    {
        if (Velocity.x > 0.f)
        {
            Velocity.x -= SlowDown;
        }
        else if (Velocity.x < 0.f)
        {
            Velocity.x += SlowDown;
        }
        
        if (Velocity.y > 0.f)
        {
            Velocity.y -= SlowDown;
        }
        else if (Velocity.y < 0.f)
        {
            Velocity.y += SlowDown;
        }
    }
}

void Ship::IncreaseVelocity()
{
    if (IsKeyDown(KEY_W) && Velocity.y >= -MaxVelocity.y) 
    {
        Velocity.y -= Stats.Speed;
    }
    if ((IsKeyDown(KEY_A) || IsKeyPressed(KEY_A)) && Velocity.x >= -MaxVelocity.x) 
    {
        Velocity.x -= Stats.Speed;
    }
    if (IsKeyDown(KEY_S) && Velocity.y <= MaxVelocity.y) 
    {
        Velocity.y += Stats.Speed;
    }
    if ((IsKeyDown(KEY_D) || IsKeyPressed(KEY_D)) && Velocity.x <= MaxVelocity.x) 
    {
        Velocity.x += Stats.Speed;
    }
}

void Ship::CheckShifting()
{
    raylib::Vector2 Quadrant{ScreenPos.Subtract(PrevScreenPos)};

    if (((Quadrant.x <= 0.f && Heading == Direction::LEFT && Heading != PrevHeading) ||
        (Quadrant.x >= 0.f && Heading == Direction::RIGHT && Heading != PrevHeading)) 
        && Stats.Speed >= 4.f && !IsKeyDown(KEY_W) && !IsKeyDown(KEY_S))
    {
        Shifting = true;
    }
}