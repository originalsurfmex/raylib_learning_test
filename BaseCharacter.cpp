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
    /* ----------- sprite animation (all chars have same # of frames) ----------- */
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.0f;
        if (frame > charSprites)
            frame = 0;
    }

    /* --------------------- character movement, speed, etc --------------------- */
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

    /* ------------------- render, scale, draw character data ------------------- */
    Rectangle charRecSrc{0.0f + (static_cast<float>(frame) * width), 0.0f, rightleft * width, height};
    Rectangle charRecDest{getScreenPos().x, getScreenPos().y, width * charScale, height * charScale};

    /* ------------------------------- show damage ------------------------------ */
    if (damage >= 75)
        DrawTexturePro(texture, charRecSrc, charRecDest, charOrigin, 0.0f, WHITE);
    else if (damage >= 50)
        DrawTexturePro(texture, charRecSrc, charRecDest, charOrigin, 0.0f, ORANGE);
    else
        DrawTexturePro(texture, charRecSrc, charRecDest, charOrigin, 0.0f, RED);
}

/* ---------------------- map boundary, collisions, etc --------------------- */
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRectangle()
{
    if (alive)
    {
        return collisionRectangle = {
                   getScreenPos().x,
                   getScreenPos().y,
                   width * scale,
                   height * scale};
    }
    else
        return collisionRectangle = {};
}