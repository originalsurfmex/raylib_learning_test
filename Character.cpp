#include "Character.h"
#include "raymath.h"

Character::Character(int screenW, int screenH) // constructor
{
    width = texture.width / charSprites;
    height = texture.height;
    screenPos = {static_cast<float>(screenW) / 2.0f - charScale * (0.5f * width),
                 static_cast<float>(screenH) / 2.0f - charScale * (0.5f * height)};
    collisionRectangle = {};
}

void Character::tick(float dt)
{
    dt = GetFrameTime();
    worldPosLastFrame = worldPos; // for map boundaries

    Vector2 direction{0.0, 0.0};

    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (IsKeyDown(KEY_LEFT_SHIFT))
        speed = 6.0;
    else
        speed = 3.0;

    if (Vector2Length(direction) != 0.0)
    {
        //normalize the vector so it has a length of 1.0
        //then scale it to the speed setting provided
        //then use subtract to move it in the negative direction
        //(so it scrolls opposite of direction keys)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.0f ? rightleft = -1.0f : rightleft = 1.0f;
        texture = run;
    }
    else
        texture = idle;

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

// map boundaries
void Character::undoMovement()
{
    worldPos = worldPosLastFrame;
}