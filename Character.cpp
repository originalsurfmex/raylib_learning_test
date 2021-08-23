#include "Character.h"
#include "raymath.h"

Character::Character(int screenW, int screenH) : windowWidth(screenW),
												 windowHeight(screenH) // constructor

{
	width = texture.width / charSprites;
	height = texture.height;
}

void Character::tick(float dt)
{
	if (IsKeyDown(KEY_A))
		velocity.x -= 1.0;
	if (IsKeyDown(KEY_D))
		velocity.x += 1.0;
	if (IsKeyDown(KEY_W))
		velocity.y -= 1.0;
	if (IsKeyDown(KEY_S))
		velocity.y += 1.0;

	if (IsKeyDown(KEY_LEFT_SHIFT))
		speed = 6.0;
	else
		speed = 3.0;

	//after all the movement keys
	BaseCharacter::tick(dt); //take all original tick moves from here

	/* --------------------------- position the sword --------------------------- */
	//add weapon movements after base class ticks
	//Rectangle weaponRecSrc{ (static_cast<float>(frame) * width), 0.0f, rightleft * width, height };
	Vector2 origin{0.0f, static_cast<float>(sword.height) * charScale};
	Vector2 offset{30, 40};

	/* ----------------------------- swing the sword ---------------------------- */
	if (rightleft < 0.0f)
	{
		origin = {static_cast<float>(sword.width) * charScale, static_cast<float>(sword.height) * charScale};
		offset = {20, 45};

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			swordRot = -25.f;
		else
			swordRot = 15.f;
	}
	else
	{
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			swordRot = 40.f;
		else
			swordRot = -5.f;
	}

	/* ----------------------------- draw the sword ----------------------------- */
	Rectangle weaponRecSrc{0.0f, 0.0f, rightleft * sword.width, static_cast<float>(sword.height)};
	Rectangle weaponRecDest{getScreenPos().x + offset.x, getScreenPos().y + offset.y,
							sword.width * charScale, sword.height * charScale};
	DrawTexturePro(sword, weaponRecSrc, weaponRecDest, origin, swordRot, WHITE);

	swordCollisionRec.x = weaponRecDest.x - origin.x;
	swordCollisionRec.y = weaponRecDest.y - origin.y;
	swordCollisionRec.width = weaponRecDest.width;
	swordCollisionRec.height = weaponRecDest.height;
}

Vector2 Character::getScreenPos()
{
	return Vector2{static_cast<float>(windowWidth) / 2.0f - charScale * (0.5f * width),
				   static_cast<float>(windowHeight) / 2.0f - charScale * (0.5f * height)};
}

Rectangle Character::getCollisionRectangle()
{
	Rectangle rectangle = BaseCharacter::getCollisionRectangle();
	rectangle.height *= 0.75f;
	rectangle.width *= 0.65f;
	return rectangle;
}