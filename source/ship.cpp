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
    CheckInput();
    Movement(); 
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
}

void Ship::SpriteTick(float DeltaTime)
{
    for (auto& Sprite:Sprites) 
    {
        Sprite.Tick(DeltaTime);
    }
}

void Ship::Movement()
{
    CheckOffScreen();
    CheckAccel();
    CheckDecel();
    UpdateScreenPos();
}

void Ship::CheckAccel()
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
    
    if (IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && !Turning)
    {
        State = Shipstate::NORMAL;
        Heading = Direction::NORMAL;
        TurnInTime = 0.f;
        TurnOutTime = 0.f;
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

void Ship::UpdateScreenPos()
{
    ScreenPos = ScreenPos.Add(Stats.Speed);
}
