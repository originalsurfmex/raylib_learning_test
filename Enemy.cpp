#include "Enemy.h"
#include "raymath.h"

// Enemy::Enemy(Vector2 pos, Vector2 charPos, Texture2D idle_tex, Texture2D run_tex) : texture(idle_tex),
//                                                                                     idle(idle_tex),
//                                                                                     run(run_tex)
Enemy::Enemy(Vector2 pos, Vector2 charPos)
{
    worldPos = pos;
    //texture = idle_tex;
    //idle = idle_tex;
    //run = run_tex;
    width = texture.width / maxFrames;
    height = texture.height;
};

void Enemy::tick(float dt)
{
    dt = GetFrameTime();
    worldPosLastFrame = worldPos; // for map boundaries

    Vector2 direction{0.0, 0.0};

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