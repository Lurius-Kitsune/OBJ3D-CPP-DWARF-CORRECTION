#pragma once
#include "Singleton.h"
#include "Coordinates.h"

class Level;

class Cursor : public Singleton<Cursor>
{
	Coords location;
	string appearance;

public:
	INLINE void SetLocation(const Coords& _location)
	{
		location = _location;
	}
	INLINE string GetAppearance() const
	{
		return appearance;
	}
	INLINE Coords GetLocation() const
	{
		return location;
	}

public:
	Cursor();

public:
	Coords GetCenterConsole() const;
	void SetCursorPosition(const u_int& _rowIndex, const u_int& _columnIndex, const bool _cursor = false) const;
	bool CheckConsoleSize(Coords& _center, Coords& _previousCenter, const string& _text, const Coords& _padding, int _height) const;
	void DisplayOnceCenterMultiLine(const vector<string> _textArray, const u_int& _size, const Coords& _padding = { 0, 0 }) const;
	void FlushInput();

	void Move(Level* _level, const Coords& _offset);
};