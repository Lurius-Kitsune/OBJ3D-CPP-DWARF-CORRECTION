#pragma once
#include "CoreMinimal.h"

struct Coords
{
	int x;
	int y;

	Coords() = default;
	Coords(const int _x, const int _y)
	{
		x = _x;
		y = _y;
	}

	string ToString() const
	{
		return  "(X : " + STRING(x)  + ", Y : " + STRING(y);
	}
};