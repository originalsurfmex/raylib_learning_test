#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

/* ---------------------- map boundary, collisions, etc --------------------- */
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}