#include "raylib.h"
class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 charVec);
    Rectangle collisionRectangle{};

private:
    Vector2 worldPos{};
    Texture2D texture{};
    Vector2 screenPos{};
    float scale{4.0f};
};
