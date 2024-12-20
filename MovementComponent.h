#pragma once
#include "Component.h"
#include "Coordinates.h"

class MovementComponent : public Component
{
	u_int speed;
	queue<Coords> path;
	Coords* targetCoords;

public:
	INLINE void SetSpeed(const u_int& _speed)
	{
		speed = _speed;
	}

private:
	INLINE bool RetrieveNextCoords()
	{
		if (path.empty()) return false;

		for (u_int _index = 0; _index < speed; _index++)
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
	void SetTargetLocation(const Coords& _targetCoords);
};