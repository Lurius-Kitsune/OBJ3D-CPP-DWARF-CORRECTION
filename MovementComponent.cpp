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
		// Je mets � jours ma destination
		// Si je suis d�j� arriver � destination
		if (!RetrieveNextCoords()) return false;
	}
	return true;
}

void MovementComponent::MoveToTarget()
{
	if (!TryGetNextCoords()) return;

	owner->SetLocation(*targetCoords);
}


void MovementComponent::Update()
{
	MoveToTarget();
}