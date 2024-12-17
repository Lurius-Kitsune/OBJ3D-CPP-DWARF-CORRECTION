#pragma once
#include "CoreMinimal.h"

class Entity;

class Component
{
protected:
	Entity* owner;

public:
	INLINE void SetOwner(Entity* _owner)
	{
		owner = _owner;
	}

public:
	virtual void Update() = 0;
};