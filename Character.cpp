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
    BaseCharacter::tick(dt); //take all original tick moves from here

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
}