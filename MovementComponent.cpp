#include "MovementComponent.h"
#include "Game.h"
#include "Entity.h"
#include "AstarAlgo.h"
#include "Cursor.h"
#include "Macro.h"

MovementComponent::MovementComponent(const u_int& _speed)
{
	speed = _speed;
	path = queue<Coords>();
	targetCoords = nullptr;
}


bool MovementComponent::TryGetNextCoords()
{
	// Si je n'ai plus de destination
	if (!targetCoords)
	{
		// Je mets à jour ma destination
		// Si je suis déjà arrivé à destination
		if (!RetrieveNextCoords()) return false;
	}

	return true;
}

void MovementComponent::MoveToTarget()
{
	if (!TryGetNextCoords()) return;

	owner->SetLocation(*targetCoords);
	targetCoords = nullptr;
}


void MovementComponent::Update()
{
	MoveToTarget();
}

void MovementComponent::SetTargetLocation(const Coords& _targetCoords)
{
	AstarAlgo<Tile> _astar = AstarAlgo<Tile>(Game::GetInstance().GetLevel()->GetMap());
	path = ToQueue(_astar.FindPath(owner->GetLocation(), _targetCoords));
}