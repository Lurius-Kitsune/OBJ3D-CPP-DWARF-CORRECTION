#pragma once
#include "Component.h"
#include "Coordinates.h"

class MovementComponent : public Component
{
	u_int moveSpeed;
	queue<Coords> path;
	Coords* targetCoords;

private:
	INLINE bool RetrieveNextCoords()
	{
		if (path.empty()) return false;

		for (u_int _index = 0; _index < moveSpeed; _index++)
		{
			targetCoords = &path.front();
			path.pop();
		}

		return true;
	}

public:
	MovementComponent(const u_int& _speed);

private:
	bool TryGetNextCoords();
	void MoveToTarget();

public:
	virtual void Update() override;
	void SetTargetLocation(const Coords& _coords);
};