#pragma once
#include "CoreMinimal.h"
#include "Level.h"
#include "Coordinates.h"
#include "Singleton.h"
class Cursor : public Singleton<Cursor>
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
	Coords GetCenterConsole() const;
	void SetCursorPosition(const u_int& _rowIndex, const u_int& _columnIndex, const bool _cursor = false) const;
	bool CheckConsoleSize(Coords& _center, Coords& _previousCenter, const string& _text, const Coords& _padding, int _height) const;
	void DisplayOnceCenterMultiLine(const vector<string> _textArray, const u_int& _size, const Coords& _padding = { 0, 0 }) const;
	void FlushInput();

	void Move(Level* _level, const Coords& _offset);
};