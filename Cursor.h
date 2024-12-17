#pragma once
#include "CoreMinimal.h"
#include "Coordinates.h"

class Cursor
{
	string appearance; 
	Coords position;

public:
	INLINE const string& GetAppearance()const
	{
		return appearance;
	}

	INLINE const Coords& GetCoords()const
	{
		return position;
	}

public:
	Cursor(const Coords& _position);

public:
	Coords GetCenterConsole();
	void SetCursorPosition(const u_int& _rowIndex, const u_int& _columnIndex, const bool _cursor = false)const;
	bool CheckConsoleSize(Coords& _center, Coords& _previousCenter, const string& _text, const Coords& _padding, int _height);
	void DisplayOnceCenterMultiLine(const string* _textArray, const u_int& _size, const Coords& _padding = { 0, 0 });
	void Move(Level* _level, const Coords& _offset);
};