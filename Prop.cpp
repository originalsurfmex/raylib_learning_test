#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) : worldPos(pos),
                                         texture(tex)
{
}

void Prop::Render(Vector2 charPos)
{
    screenPos = Vector2Subtract(worldPos, charPos);
    //Rectangle charRecSrc{origin.x, origin.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    //Rectangle charRecDest{screenPos.x, screenPos.y, texture.width * scale, texture.height * scale};
    //DrawTexturePro(texture, charRecSrc, charRecDest, origin, 0.0f, WHITE);
    DrawTextureEx(texture, screenPos, 0.0f, scale, WHITE);
}

//trying to figure out how to stop rock from glitching if drawn after character
// void Prop::tick(float dt, Vector2 charPos)
// {
//     dt = GetFrameTime();
//     worldPosLastFrame = worldPos;
//     screenPos = Vector2Subtract(worldPos, charPos);

//     runningTime += dt;
//     if (runningTime >= updateTime)
//         runningTime = 0;

//     DrawTextureEx(texture, screenPos, 0.0f, scale, WHITE);
// }

// void Prop::undoMovement()
// {
//     worldPos = worldPosLastFrame;
// }