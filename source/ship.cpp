#include "ship.hpp"

Ship::Ship() 
{
    health = 100.f;
    texture = idle;
    width = static_cast<float>(texture.width/8);
    height = static_cast<float>(texture.height/7);
    bulletWidth = static_cast<float>(projectile.width/8);
    bulletHeight = static_cast<float>(projectile.height);
}

Ship::~Ship()
{
    UnloadTexture(idle);
    UnloadTexture(accel);
    UnloadTexture(decel);
    UnloadTexture(projectile);
}

void Ship::tick(float DeltaTime)
{
    // Movement
    if (IsKeyPressed(KEY_W)) texture = accel;
    if (IsKeyDown(KEY_W)) ScreenPos.y -= speed;
    if (IsKeyReleased(KEY_W)) texture = idle;
    if (IsKeyPressed(KEY_S)) texture = decel;
    if (IsKeyDown(KEY_S)) ScreenPos.y += speed - 1.5f;
    if (IsKeyReleased(KEY_S)) texture = idle;
    
    if (IsKeyDown(KEY_A)) 
    {
        sourceY = 2 * height;
        ScreenPos.x -= speed;
    }
    if (IsKeyPressed(KEY_A)) sourceY = 1 * height;
    if (IsKeyUp(KEY_A)) sourceY = 0;
    if (IsKeyReleased(KEY_A)) sourceY = 3 * height;

    if (IsKeyDown(KEY_D)) 
    {
        sourceY = 5 * height;
        ScreenPos.x += speed;
    }
    if (IsKeyPressed(KEY_D)) sourceY = 4 * height;
    if (IsKeyReleased(KEY_D)) sourceY = 6 * height;

    // Screen dimension borders
    if (ScreenPos.x + scale*width < 0) ScreenPos.x = Window::Dimension.x;
    if (ScreenPos.x > Window::Dimension.x) ScreenPos.x = 0 - scale*width;
    if (ScreenPos.y < 0) ScreenPos.y = 0;
    if (ScreenPos.y > Window::Dimension.y - scale*height) ScreenPos.y = Window::Dimension.y - scale*height;

    BaseCharacter::tick(DeltaTime);

    // draw main texture
    Rectangle source{currentFrame * width, sourceY, width, height};
    Rectangle dest{ScreenPos.x, ScreenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);

    // draw projectile
    // if (IsKeyDown(KEY_SPACE)) 
    // {
    //     // Bullets.at(1).Tick(DeltaTime);
    //     Rectangle bulletSource{currentFrame * bulletWidth, bulletHeight, bulletWidth, bulletHeight};
    //     Rectangle bulletDest{ScreenPos.x + scale*width/2-6, ScreenPos.y - height, 3 * bulletWidth, 3 * bulletHeight};
    //     DrawTexturePro(projectile, bulletSource, bulletDest, Vector2{0.f, 0.f}, 0.f, WHITE);
    // }
}