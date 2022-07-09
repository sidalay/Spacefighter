#include "ship.hpp"

Ship::Ship(const GameTexture& Textures, 
           const GameAudio& Audio, 
           const raylib::Window& Window,
           const Shipcolor Shade)
    : Textures{Textures}, Audio{Audio}, Shade{Shade}, Window{Window}
{
    ScreenPos = raylib::Vector2{static_cast<float>(Window.GetWidth()/2), static_cast<float>(Window.GetHeight()/2)};

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
    CheckDirection();
    CheckSpriteIndex();
    CheckOffScreen();
    SpriteTick(DeltaTime);

    // // draw main Texture
    // Rectangle source{currentFrame * width, sourceY, width, height};
    // Rectangle dest{ScreenPos.x, ScreenPos.y, scale * width, scale * height};
    // DrawTexturePro(Texture, source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);
}

void Ship::Draw()
{
    DrawTexturePro(Sprites.at(SpriteIndex).Texture, 
                   Sprites.at(SpriteIndex).GetSourceRec(), 
                   Sprites.at(SpriteIndex).GetPosRec(ScreenPos, Scale), 
                   raylib::Vector2{}, 0.f, WHITE);
}

void Ship::SpriteTick(float DeltaTime)
{
    for (auto& Sprite:Sprites) {
        Sprite.Tick(DeltaTime);
    }
}

void Ship::Movement()
{
    if (IsKeyDown(KEY_W)) 
    {
        ScreenPos.y -= Speed;
    }
    if (IsKeyDown(KEY_A) || IsKeyPressed(KEY_A)) 
    {
        ScreenPos.x -= Speed;
    }
    if (IsKeyDown(KEY_S)) 
    {
        ScreenPos.y += Brakespeed;
    }
    if (IsKeyDown(KEY_D) || IsKeyPressed(KEY_D)) 
    {
        ScreenPos.x += Speed;
    }
}

void Ship::CheckInput()
{
    bool TurningLeft{Flying == Direction::LEFT || Flying == Direction::SUBTLELEFT};
    bool TurningRight{Flying == Direction::RIGHT || Flying == Direction::SUBTLERIGHT};
    bool Turning{TurningLeft || TurningRight};
    bool TurnLeftRelease{
        (IsKeyUp(KEY_A) && TurningLeft) ||
        (IsKeyUp(KEY_A) && IsKeyDown(KEY_W) && (TurningLeft && Flying == Direction::UP)) ||
        (IsKeyUp(KEY_A) && IsKeyDown(KEY_S) && (TurningLeft && Flying == Direction::DOWN))
    };
    bool TurnRightRelease{
        (IsKeyUp(KEY_D) && TurningRight) ||
        (IsKeyUp(KEY_D) && IsKeyDown(KEY_W) && (TurningRight && Flying == Direction::UP)) ||
        (IsKeyUp(KEY_D) && IsKeyDown(KEY_S) && (TurningRight && Flying == Direction::DOWN))
    };
    float MaxTurningTime{1.f/11.f};

    if (IsKeyDown(KEY_W)) 
    {
        State = Shipstate::ACCELERATE;
        Flying = Direction::UP;
    }
    else if (IsKeyDown(KEY_S)) 
    {
        State = Shipstate::DECELERATE;
        Flying = Direction::DOWN;
    }

    if (IsKeyDown(KEY_A)) 
    {
        TurnInTime += GetFrameTime();
        Turning = true;

        if (TurnInTime <= MaxTurningTime) 
        {
            Flying = Direction::SUBTLELEFT;
        }
        else 
        {
            Flying = Direction::LEFT;
        }
    }

    if (IsKeyDown(KEY_D)) 
    {
        TurnInTime += GetFrameTime();
        Turning = true;

        if (TurnInTime <= MaxTurningTime) 
        {
            Flying = Direction::SUBTLERIGHT;
        }
        else 
        {
            Flying = Direction::RIGHT;
        }
    }

    if (TurnLeftRelease)
    {
        TurnOutTime += GetFrameTime();
        
        if (TurnOutTime <= MaxTurningTime) 
        {
            Flying = Direction::SUBTLELEFT;
        }
        else 
        {
            Turning = false;
            TurnInTime = 0.f;
            TurnOutTime = 0.f;
            Flying = Direction::NORMAL;
        }
    }
    if (TurnRightRelease)
    {
        TurnOutTime += GetFrameTime();
        
        if (TurnOutTime <= MaxTurningTime) 
        {
            Flying = Direction::SUBTLERIGHT;
        }
        else 
        {
            Turning = false;
            TurnInTime = 0.f;
            TurnOutTime = 0.f;
            Flying = Direction::NORMAL;
        }
    }
    
    if (IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D) && !Turning)
    {
        State = Shipstate::NORMAL;
        Flying = Direction::NORMAL;
        TurnInTime = 0.f;
        TurnOutTime = 0.f;
    }
}

void Ship::CheckDirection()
{
    switch (Flying)
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

void Ship::CheckSpriteIndex()
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
