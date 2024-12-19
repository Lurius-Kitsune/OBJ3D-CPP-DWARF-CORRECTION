#pragma once
#include "CoreMinimal.h"
#include "Size.h"

struct Size;

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
	Coords(const Size& _size)
	{
		x = _size.x;
		y = _size.y;
	}

	string ToString() const
	{
		return "X: " + STRING(x) + " Y:" + STRING(y);
	}

	bool operator == (const Coords& _other) const
	{
		return x == _other.x
			&& y == _other.y;
	}
	Coords& operator += (const Coords& _other)
	{
		x += _other.x;
		y += _other.y;
		return *this;
	}
};