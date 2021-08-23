#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
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
    /* --------------------------- chase the character -------------------------- */
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < hitRadius)
        velocity = {};

    BaseCharacter::tick(dt);
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

Rectangle Enemy::getCollisionRectangle()
{
	Rectangle rectangle = BaseCharacter::getCollisionRectangle();
	rectangle.height *= 0.65f;
	rectangle.width *= 0.65f;
	return rectangle;
}