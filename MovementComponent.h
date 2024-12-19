#pragma once
#include "Component.h"
#include "Coordinates.h"

class MovementComponent : public Component
{
	u_int moveSpeed;
	queue<Coords> path;

public:
	MovementComponent(const u_int& _speed);

public:
	virtual void Update() override;
};