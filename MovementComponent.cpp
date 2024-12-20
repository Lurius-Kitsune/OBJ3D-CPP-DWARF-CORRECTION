#include "MovementComponent.h"
#include "Macro.h"
#include "Entity.h"
MovementComponent::MovementComponent(const u_int& _speed)
{
	moveSpeed = _speed;
	path = queue<Coords>();
	targetCoords = nullptr;
}

bool MovementComponent::TryGetNextCoords()
{
	// Plus de destination
	if (!targetCoords)
	{
		// Je mets à jours ma destination
		// Si je suis déjà arriver à destination
		if (!RetrieveNextCoords()) return false;
	}
	return true;
}

void MovementComponent::MoveToTarget()
{
	if (!TryGetNextCoords()) return;

	owner->SetLocation(*targetCoords);
}

void MovementComponent::SetTargetLocation(const Coords& _coords)
{

}


void MovementComponent::Update()
{
	MoveToTarget();
}