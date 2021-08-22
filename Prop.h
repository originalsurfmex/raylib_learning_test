#include "raylib.h"
#include "Character.h"
class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void Render();
    Rectangle getCollisionRectangle();
    Vector2 getScreenPos();
    void setTarget(Character *character) {target = character;}

private:
    Vector2 worldPos{};
    Texture2D texture{};
    Vector2 screenPos{};
    float scale{4.0f};
    Character *target;

protected:
    float width{};
    float height{};
};
