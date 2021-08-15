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
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);

    // normalize toTarget vector
    toTarget = Vector2Normalize(toTarget);

    // multiply toTarget vector by speed of goon
    toTarget = Vector2Scale(toTarget, speed);

    // move that goon  
    worldPos = Vector2Add(worldPos, toTarget);
    screenPos = Vector2Subtract(worldPos, target->getWorldPos());

    BaseCharacter::tick(dt);
}