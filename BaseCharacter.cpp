#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

/* ------------------------------ tick function ----------------------------- */
void BaseCharacter::tick(float dt)
{
    worldPosLastFrame = worldPos; // for map boundaries

    runningTime += dt;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > charSprites)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        //normalize the vector so it has a length of 1.0
        //then scale it to the speed setting provided
        //then use subtract to move it in the negative direction
        //(so it scrolls opposite of direction keys)
        //set world pos = worldpos + velocity
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.0f ? rightleft = -1.0f : rightleft = 1.0f;
        texture = run;
    }
    else
        texture = idle;
    velocity = {}; // reset the velocity each frame

    Rectangle charRecSrc{0.0f + (static_cast<float>(frame) * width), 0.0f, rightleft * width, height};
    Rectangle charRecDest{getScreenPos().x, getScreenPos().y, width * charScale, height * charScale};
    DrawTexturePro(texture, charRecSrc, charRecDest, charOrigin, 0.0f, WHITE);
}

/* ---------------------- map boundary, collisions, etc --------------------- */
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRectangle()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale};
}