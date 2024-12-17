#pragma once
#include "CoreMinimal.h"
#include "Emoji.h"
#include "Tile.h"

struct Size
{
	int x;
	int y;

	Size() = default;
	Size(const int _sizeX, const int _sizeY)
	{
		x = _sizeX;
		y = _sizeY;
	}
	Size(const vector<vector<Tile>>& _map)
	{
		if (_map.empty()) return;

		x = int(_map.size());
		y = int(_map[0].size());
	}

	string ToString() const
	{
		return "Size => " + STRING(x) + "/" + STRING(y);
	}

	Size operator / (const int _value) const
	{
		assert(_value != 0 && "Impossible de diviser par 0 !");

		return
		{
			x / _value,
			y / _value
		};
	}
};
