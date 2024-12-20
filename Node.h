#pragma once
#include "CoreMinimal.h"
#include "Coordinates.h"

struct Node
{
	Coords location;
	u_int g;
	u_int h;
	Node* parent;

	Node(const Coords& _location, const u_int& _gCost, const u_int& _hCost, Node* _parent)
	{
		location = _location;
		g = _gCost;
		h = _hCost;
		parent = _parent;
	}

	INLINE u_int GetF()const
	{
		return g + h;
	}
};