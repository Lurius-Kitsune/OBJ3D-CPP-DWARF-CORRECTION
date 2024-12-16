#pragma once
#include "CoreMinimal.h"
#include "Size.h"

struct Coords
{
	int y;
	int x;

	Coords() = default;
	Coords(const int _x, const int _y)
	{
		x = _x;
		y = _y;
	}
	Coords(const Size& _size)
	{
		x = _size.sizeX;
		y = _size.sizeY;
	}

	string ToString() const
	{
		return  "(X : " + STRING(x)  + ", Y : " + STRING(y);
	}
};