#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character(int screenW, int screenH);
    virtual void tick(float dt) override;
    virtual Vector2 getScreenPos() override;
    virtual Rectangle getCollisionRectangle() override;
    Rectangle getSwordCollision() { return swordCollisionRec; }

private:
    int windowWidth{};
    int windowHeight{};

	//sword
	Texture2D sword{ LoadTexture("characters/weapon_sword.png") };
    Rectangle swordCollisionRec{ 0.0f, 0.0f, 
        static_cast<float>(sword.width), static_cast<float>(sword.height) };
	float swordRot{};
};

#endif
