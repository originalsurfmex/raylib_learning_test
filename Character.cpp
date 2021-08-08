#include "Character.h"
#include "raymath.h"

Character::Character(int screenW, int screenH) // constructor
{
    width = texture.width / charSprites;
    height = texture.height;
    screenVec = {(float)screenW / 2.0f - charScale * (0.5f * width),
                 (float)screenH / 2.0f - charScale * (0.5f * height)};
}

// void Character::setScreenVec(int winW, int winH)
// {
//     screenVec = {
//         (float)winW / 2.0f - charScale * (0.5f * width),
//         (float)winH / 2.0f - charScale * (0.5f * height)};
// }

void Character::tick(float dt)
{
    //dt = GetFrameTime();
    worldVecLastFrame = worldVec; // for map boundaries

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
        worldVec = Vector2Add(worldVec, Vector2Scale(Vector2Normalize(direction), speed));
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

    Rectangle charRecSrc{0.0f + ((float)frame * width), 0.0f, rightleft * width, height};
    Rectangle charRecDest{screenVec.x, screenVec.y, width * charScale, height * charScale};
    DrawTexturePro(texture, charRecSrc, charRecDest, charOrigin, 0.0f, WHITE);
}

// map boundaries
void Character::undoMovement()
{
    worldVec = worldVecLastFrame;
}