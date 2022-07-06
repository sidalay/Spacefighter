#include "ship.hpp"

Ship::Ship(const GameTexture& Textures, const GameAudio& Audio, const raylib::Vector2I& Screen)
    : Textures{Textures}, Audio{Audio}, Screen{Screen}
{
    // Health = 100.f;
    // Texture = Idle;
    // Width = static_cast<float>(Texture.width/8);
    // Height = static_cast<float>(Texture.height/7);
}

void Ship::Tick(float DeltaTime)
{
    // // Movement
    // if (IsKeyPressed(KEY_W)) Texture = accel;
    // if (IsKeyDown(KEY_W)) ScreenPos.y -= speed;
    // if (IsKeyReleased(KEY_W)) Texture = idle;
    // if (IsKeyPressed(KEY_S)) Texture = decel;
    // if (IsKeyDown(KEY_S)) ScreenPos.y += speed - 1.5f;
    // if (IsKeyReleased(KEY_S)) Texture = idle;
    
    // if (IsKeyDown(KEY_A)) 
    // {
    //     sourceY = 2 * height;
    //     ScreenPos.x -= speed;
    // }
    // if (IsKeyPressed(KEY_A)) sourceY = 1 * height;
    // if (IsKeyUp(KEY_A)) sourceY = 0;
    // if (IsKeyReleased(KEY_A)) sourceY = 3 * height;

    // if (IsKeyDown(KEY_D)) 
    // {
    //     sourceY = 5 * height;
    //     ScreenPos.x += speed;
    // }
    // if (IsKeyPressed(KEY_D)) sourceY = 4 * height;
    // if (IsKeyReleased(KEY_D)) sourceY = 6 * height;

    // // Screen dimension borders
    // if (ScreenPos.x + scale*width < 0) ScreenPos.x = Window::Dimension.x;
    // if (ScreenPos.x > Window::Dimension.x) ScreenPos.x = 0 - scale*width;
    // if (ScreenPos.y < 0) ScreenPos.y = 0;
    // if (ScreenPos.y > Window::Dimension.y - scale*height) ScreenPos.y = Window::Dimension.y - scale*height;

    // BaseCharacter::Tick(DeltaTime);

    // // draw main Texture
    // Rectangle source{currentFrame * width, sourceY, width, height};
    // Rectangle dest{ScreenPos.x, ScreenPos.y, scale * width, scale * height};
    // DrawTexturePro(Texture, source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);

    // draw projectile
    // if (IsKeyDown(KEY_SPACE)) 
    // {
    //     // Bullets.at(1).Tick(DeltaTime);
    //     Rectangle bulletSource{currentFrame * bulletWidth, bulletHeight, bulletWidth, bulletHeight};
    //     Rectangle bulletDest{ScreenPos.x + scale*width/2-6, ScreenPos.y - height, 3 * bulletWidth, 3 * bulletHeight};
    //     DrawTexturePro(projectile, bulletSource, bulletDest, Vector2{0.f, 0.f}, 0.f, WHITE);
    // }
}