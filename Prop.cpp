#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos),
                                         texture(tex)
{
}

void Prop::Render(Vector2 charPos)
{
    screenPos = Vector2Subtract(worldPos, charPos);
    DrawTextureEx(texture, screenPos, 0.0f, scale, WHITE);
    collisionRectangle = {screenPos.x, screenPos.y,
                          static_cast<float>(texture.width * scale),
                          static_cast<float>(texture.height * scale)};
}