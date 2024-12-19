#include "Cursor.h"
#include "Color.h"
#include "Level.h"
#include "Emoji.h"
#include "Macro.h"

Cursor::Cursor()
{
	appearance = CROSSHAIR;
}


Coords Cursor::GetCenterConsole() const
{
	CONSOLE_SCREEN_BUFFER_INFO _csbi;
	int _ys, _xs;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
	_ys = _csbi.srWindow.Right - _csbi.srWindow.Left;
	_xs = _csbi.srWindow.Bottom - _csbi.srWindow.Top;
	return { _ys, _xs };
}

void Cursor::SetCursorPosition(const u_int& _xIndex, const u_int& _yIndex, const bool _cursor) const
{
	static const HANDLE _hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO _info;
	std::cout.flush();
	_info.dwSize = 100;
	_info.bVisible = _cursor;
	COORD coord = { (SHORT)_xIndex, (SHORT)_yIndex };
	SetConsoleCursorInfo(_hOut, &_info);
	SetConsoleCursorPosition(_hOut, coord);
}

bool Cursor::CheckConsoleSize(Coords& _center, Coords& _previousCenter, const string& _text, const Coords& _padding, int _height) const
{
	if (_height < 1) _height = 1;
	const regex& _regex = regex("x1b[(38|48);2;[0-9]{1,3};[0-9]{1,3};[0-9]{1,3}m|\x1b[[0-9;]*[mKHVfF]"); // Regex pour supprimer les codes ANSI
	const int _size = (int)regex_replace(_text, _regex, "").size();

	const string& _errorText = "Agrandissez la taille de la console !";
	_center = GetCenterConsole();
	if (_previousCenter.x != _center.x || _previousCenter.y != _center.y) system("cls");

	if (_center.x + _padding.x < _size || _center.y + _padding.y < _height)
	{
		if (_errorText.size() > _center.x)
		{
			system("cls");
			return true;
		}
		SetCursorPosition((_center.x - u_int(_errorText.size())) / 2, 0);
		cout << BLINK_COLOR(RED) << _errorText << RESET;
		_previousCenter = _center;
		return true;
	}
	return false;
}

void Cursor::DisplayOnceCenterMultiLine(const vector<string> _textArray, const u_int& _size, const Coords& _padding) const
{
	Coords _center = GetCenterConsole();
	Coords _previousCenter = _center;
	const regex& _regex = regex("x1b[(38|48);2;[0-9]{1,3};[0-9]{1,3};[0-9]{1,3}m|\x1b[[0-9;]*[mKHVfF]"); // Regex pour supprimer les codes ANSI

	for (u_int _index = 0; _index < _size; _index++)
	{
		const int _lineSize = (int)regex_replace(_textArray[_index], _regex, "").size();
		if (CheckConsoleSize(_center, _previousCenter, _textArray[_index], _padding, _size)) continue;
		SetCursorPosition(((_center.x + _padding.x) - u_int(_lineSize)) / 2, (_center.y + (2 * ((_padding.y - _size) / 2 + _index))) / 2);
		cout << _textArray[_index];
		_previousCenter = _center;
	}
}

void Cursor::FlushInput()
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void Cursor::Move(Level* _level, const Coords& _offset)
{
	if (!_level->IsValidCoords(location + _offset)) return;
}