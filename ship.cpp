#include "ship.h"

Ship::Ship()
{
    health = 100.f;
    texture = idle;
    width = static_cast<float>(texture.width/8);
    height = static_cast<float>(texture.height/7);
}

void Ship::tick(float DeltaTime)
{
    if (IsKeyPressed(KEY_W))texture = accel;
    if (IsKeyReleased(KEY_W)) texture = idle;
    if (IsKeyPressed(KEY_S))texture = decel;
    if (IsKeyReleased(KEY_S)) texture = idle;
    
    if (IsKeyDown(KEY_A )) sourceY = 2 * height;
    if (IsKeyPressed(KEY_A)) sourceY = 1 * height;
    if (IsKeyUp(KEY_A)) sourceY = 0;
    if (IsKeyReleased(KEY_A)) sourceY = 3 * height;

    if (IsKeyDown(KEY_D)) sourceY = 5 * height;
    if (IsKeyPressed(KEY_D)) sourceY = 4 * height;
    if (IsKeyReleased(KEY_D)) sourceY = 6 * height;


    BaseCharacter::tick(DeltaTime);


    // draw main texture
    Rectangle source{currentFrame * width, sourceY, width, height};
    Rectangle dest{640, 360, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{0.f, 0.f}, 0.f, WHITE);
}