#include "MovementComponent.h"
#include "Macro.h"

MovementComponent::MovementComponent(const u_int& _speed)
{
	moveSpeed = _speed;
}


void MovementComponent::Update()
{
	Print("", "Bonjour !");
}