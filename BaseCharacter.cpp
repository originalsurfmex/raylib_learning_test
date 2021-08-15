#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

/* ------------------------------ tick function ----------------------------- */
void BaseCharacter::tick(float dt)
{
    dt = GetFrameTime();
    worldPosLastFrame = worldPos; // for map boundaries



    runningTime += dt;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > charSprites)
            frame = 0;
    }

    Rectangle charRecSrc{0.0f + (static_cast<float>(frame) * width), 0.0f, rightleft * width, height};
    Rectangle charRecDest{screenPos.x, screenPos.y, width * charScale, height * charScale};
    DrawTexturePro(texture, charRecSrc, charRecDest, charOrigin, 0.0f, WHITE);
    /* --------------------------- collision rectangle -------------------------- */
    collisionRectangle = {screenPos.x, screenPos.y, charRecDest.width, charRecDest.height};
}

/* ---------------------- map boundary, collisions, etc --------------------- */
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}