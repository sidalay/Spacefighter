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
    CheckInput();
    CheckDirection();
    CheckSpriteIndex();
    CheckOffScreen();
    Movement(); 
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
    switch (State)
    {
        case Shipstate::ACCELERATE:
            ScreenPos.y -= Speed;
            break;
        case Shipstate::DECELERATE:
            ScreenPos.y += Brakespeed;
            break;
        default:
            break;
    }

    switch (Flying)
    {
        case Direction::LEFT:
        case Direction::SUBTLELEFT:
            ScreenPos.x -= Speed;
            break;
        case Direction::RIGHT:
        case Direction::SUBTLERIGHT:
            ScreenPos.x += Speed;
            break;
        default: 
            break;
    }
}

void Ship::CheckInput()
{
    if (IsKeyDown(KEY_W)) 
    {
        Flying = Direction::UP;
        State = Shipstate::ACCELERATE;
    }
    else if (IsKeyDown(KEY_S)) 
    {
        Flying = Direction::DOWN;
        State = Shipstate::DECELERATE;
    }
    else if (IsKeyReleased(KEY_W) && IsKeyReleased(KEY_S))
    {
        State = Shipstate::NORMAL;
    }

    if (IsKeyDown(KEY_A)) 
    {
        Flying = Direction::LEFT;
    }
    else if (IsKeyPressed(KEY_A)) 
    {
        Flying = Direction::SUBTLELEFT;
    }
    else if (IsKeyReleased(KEY_A))
    {
        Flying = Direction::RETURNLEFT;
    }

    if (IsKeyDown(KEY_D)) 
    {
        Flying = Direction::RIGHT;
    }
    else if (IsKeyPressed(KEY_D))
    {
        Flying = Direction::SUBTLERIGHT;
    }
    else if (IsKeyReleased(KEY_D))
    {
        Flying = Direction::RETURNRIGHT;
    }
}

void Ship::CheckDirection()
{
    switch (Flying)
    {
        case Direction::DOWN: 
            Sprites.at(SpriteIndex).Frame.y = 0;
            break;
        case Direction::LEFT: 
            Sprites.at(SpriteIndex).Frame.y = 2;
            break;
        case Direction::RIGHT:
            Sprites.at(SpriteIndex).Frame.y = 5;
            break;
        case Direction::UP: 
            Sprites.at(SpriteIndex).Frame.y = 0;
            break;
        case Direction::SUBTLELEFT:
            Sprites.at(SpriteIndex).Frame.y = 1;
            break;
        case Direction::SUBTLERIGHT:
            Sprites.at(SpriteIndex).Frame.y = 4;
            break;
        case Direction::RETURNLEFT:
            Sprites.at(SpriteIndex).Frame.y = 3;
            break;
        case Direction::RETURNRIGHT:
            Sprites.at(SpriteIndex).Frame.y = 6;
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
