#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int screenW, int screenH);
    virtual void tick(float dt) override;
    Vector2 getScreenPos() { return screenPos; }

private:
    /* --- commented out to figure out how to include without messing up goon --- */
    // Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    // Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    // Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
};

#endif
