// #include "headers/projectile.hpp"

// Projectile::Projectile(Vector2 ShipScreenPos)
//     : ScreenPos{ShipScreenPos},
//       bulletWidth{static_cast<float>(Bullet.width/8)},
//       bulletHeight{static_cast<float>(Bullet.height)} 
// {

// }

// Projectile::~Projectile() 
// {
//     UnloadTexture(Bullet);
// }

// void Projectile::Tick(float deltaTime)
// {
//     // update animation frame
//     runningTime += deltaTime;
//     if (runningTime >= updateTime)
//     {
//         previousFrame = currentFrame;
//         ++currentFrame;
//         runningTime = 0.f;
//         if (currentFrame > maxFrames) currentFrame = 0;
//     }

//     // draw
//     if (ScreenPos.y - height > 0) {
//         Rectangle bulletSource{currentFrame * bulletWidth, bulletHeight, bulletWidth, bulletHeight};
//         Rectangle bulletDest{ScreenPos.x + scale*width/2-6, ScreenPos.y - height, 3 * bulletWidth, 3 * bulletHeight};
//         DrawTexturePro(Bullet, bulletSource, bulletDest, Vector2{0.f, 0.f}, 0.f, WHITE);
//         bulletDest.y += 20.f;
//     }

//     // check where it is on the screen and call destructor when it reaches a certain point


// }