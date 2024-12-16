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

	bool operator== (const Coords&& _other)const
	{
		return x == _other.x && y == _other.y;
	}

	Coords& operator += (const Coords& _other)
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}
};