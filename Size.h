#pragma once

struct Size
{
	int sizeX;
	int sizeY;

	Size() = default;
	Size(const vector<string>& _map)
	{

		sizeX = int(_map[0].size());
		sizeY = int(_map.size());
	}
	Size(const int _x, const int _y)
	{
		sizeX = _x;
		sizeY = _y;
	}

	string ToString() const
	{
		return  "(SizeX : " + STRING(sizeX) + ", SizeY : " + STRING(sizeY);
	}

	Size operator/(const int _value) const
	{
		assert(_value != 0 && "Impossible de diviser par 0");

		return
		{
			sizeX / _value,
			sizeY / _value
		};
	}
};