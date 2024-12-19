#pragma once
#include "CoreMinimal.h"
#include "Level.h"
#include "Coordinates.h"

class Cursor
{
	Coords location;
	string appearance;

public:
	INLINE string GetAppearance() const
	{
		return appearance;
	}
	INLINE Coords GetLocation() const
	{
		return location;
	}

public:
	Cursor() = default;
	Cursor(const Coords& _location);

public:
	Coords GetCenterConsole();
	void SetCursorPosition(const u_int& _rowIndex, const u_int& _columnIndex, const bool _cursor = false) const;
	bool CheckConsoleSize(Coords& _center, Coords& _previousCenter, const string& _text, const Coords& _padding, int _height);
	void DisplayOnceCenterMultiLine(const vector<string> _textArray, const u_int& _size, const Coords& _padding = { 0, 0 });

	void Move(Level* _level, const Coords& _offset);
};