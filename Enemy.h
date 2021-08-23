#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_text, Texture2D run_tex);
    virtual void tick(float dt) override;
    void setTarget(Character* character) {target = character;} 
    virtual Vector2 getScreenPos() override;
    virtual Rectangle getCollisionRectangle() override;

private:
    Character* target;
};