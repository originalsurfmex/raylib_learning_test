#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int screenW, int screenH);
    virtual void tick(float dt) override;
    //Vector2 getScreenPos() { return screenPos; }
    virtual Vector2 getScreenPos() override;

private:
    int windowWidth{};
    int windowHeight{};
};

#endif
