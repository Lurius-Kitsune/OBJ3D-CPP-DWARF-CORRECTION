#pragma once
#include "CoreMinimal.h"
#include "Coordinates.h"

template <typename Type>
class AstarAlgo
{
	u_int width;
	u_int weight;
	vector<vector<Type>> grid;
public:
	INLINE u_int Heuristic(const Coords& _coordsA, const Coords& _coordsB)const
	{
		return abs(_coordsA.x - _coordsB.x) + abs(_coordsA.y - _coordsB.y);
	}

public:
	AstarAlgo(const vector<vector<Type>>& _grid)
	{
		grid = _grid;
	}

private:

};

