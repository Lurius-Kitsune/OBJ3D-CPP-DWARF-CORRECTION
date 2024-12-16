#pragma once
#include "CoreMinimal.h"
#include "Cordinates.h"

struct Cursor
{
	Coords GetCenterConsole();
	void SetCursorPosition(const u_int& _rowIndex, const u_int& _columnIndex, const bool _cursor = false);
	bool CheckConsoleSize(Coords& _center, Coords& _previousCenter, const string& _text, const Coords& _padding, int _height);
	void DisplayOnceCenterMultiLine(const string* _textArray, const u_int& _size, const Coords& _padding = { 0, 0 });
};