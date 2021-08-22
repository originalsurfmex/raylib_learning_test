#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos),
                                         texture(tex)
{
    width = static_cast<float>(texture.width);
    height = static_cast<float>(texture.height);
}

Vector2 Prop::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}

Rectangle Prop::getCollisionRectangle()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale};
}

void Prop::Render()
{
    DrawTextureEx(texture, getScreenPos(), 0.0f, scale, WHITE);
}