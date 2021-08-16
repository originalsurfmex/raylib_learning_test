#include "Character.h"
#include "raymath.h"

Character::Character(int screenW, int screenH) : windowWidth(screenW),
                                                 windowHeight(screenH) // constructor

{
    width = texture.width / charSprites;
    height = texture.height;
    collisionRectangle = {};
}

void Character::tick(float dt)
{
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    if (IsKeyDown(KEY_LEFT_SHIFT))
        speed = 6.0;
    else
        speed = 3.0;

    //after all the movement keys
    BaseCharacter::tick(dt); //take all original tick moves from here
}

Vector2 Character::getScreenPos()
{
    return Vector2{static_cast<float>(windowWidth) / 2.0f - charScale * (0.5f * width),
                   static_cast<float>(windowHeight) / 2.0f - charScale * (0.5f * height)};
}