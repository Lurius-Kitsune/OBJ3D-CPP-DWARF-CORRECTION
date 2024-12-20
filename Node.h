#pragma once
#include "CoreMinimal.h"
#include "Coordinates.h"

struct Node
{
	Coords location;
	u_int g;
	u_int h;
	Node* parent;

	INLINE u_int Heuristic(const Coords& _coordsA, const Coords& _coordsB)const
	{
		return abs(_coordsA.x - _coordsB.x) + abs(_coordsA.y - _coordsB.y);
	}

	Node(const Coords& _location, const Coords& _end, Node* _parent)
	{
		location = _location;
		g = _parent ? _parent->g + 1 : 0;
		h = Heuristic(location, _end);;
		parent = _parent;
	}

	INLINE u_int GetF()const
	{
		return g + h;
	}
};