#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
//Enemy::Enemy(Vector2 pos, Vector2 charPos)
{
    worldPos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxFrames;
    height = texture.height;
};

void Enemy::tick(float dt)
{
    // get toTarget vector
    // normalize toTarget vector
    // multiply toTarget vector by speed of goon
    // move that goon  
    //Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);
    //toTarget = Vector2Normalize(toTarget);
    //toTarget = Vector2Scale(toTarget, speed);
    //worldPos = Vector2Add(worldPos, toTarget);
    //screenPos = Vector2Subtract(worldPos, target->getWorldPos());

    /* ---------- all of the above is replaced by velocity in one line ---------- */
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    BaseCharacter::tick(dt);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}