#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
    Enemy(Vector2 pos, Texture2D idle_text, Texture2D run_tex);
    virtual void tick(float dt) override;
    void setTarget(Character* character) {target = character;} 

private:
/* --------- the textures need to be commented out because Character -------- */
/* ---------- has them too and its an #include, causes weird issues --------- */
    //Texture2D texture{LoadTexture("characters/goblin_idle_spritesheet.png")};
    //Texture2D idle{LoadTexture("characters/goblin_idle_spritesheet.png")};
    //Texture2D run{LoadTexture("characters/goblin_run_spritesheet.png")};
    Character* target;
};