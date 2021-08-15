#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Vector2 charPos, Texture2D idle_tex, Texture2D run_tex)
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
    BaseCharacter::tick(dt);
}