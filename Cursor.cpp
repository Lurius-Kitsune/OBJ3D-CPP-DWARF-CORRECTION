#include "Cursor.h"
#include "Color.h"
#include "Macro.h"
#include "Emoji.h"
#include "Level.h"
Cursor::Cursor(const Coords& _position)
{
	appearance = CROSSHAIR;
	position = _position;
}

Coords Cursor::GetCenterConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO _csbi;
	int _ys, _xs;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
	_ys = _csbi.srWindow.Right - _csbi.srWindow.Left;
	_xs = _csbi.srWindow.Bottom - _csbi.srWindow.Top;
	return { _ys, _xs };
}

void Cursor::SetCursorPosition(const u_int& _xIndex, const u_int& _yIndex, const bool _cursor)const
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

bool Cursor::CheckConsoleSize(Coords& _center, Coords& _previousCenter, const string& _text, const Coords& _padding, int _height)
{
	if (_height < 1) _height = 1;
	const string& _errorText = "Agrandissez la taille de la console !";
	_center = GetCenterConsole();
	if (_previousCenter.x != _center.x || _previousCenter.y != _center.y) system("cls");

	if (_center.x + _padding.x < _text.size() || _center.y + _padding.y < _height)
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

void Cursor::DisplayOnceCenterMultiLine(const string* _textArray, const u_int& _size, const Coords& _padding)
{
	Coords _center = GetCenterConsole();
	Coords _previousCenter = _center;
	for (u_int _index = 0; _index < _size; _index++)
	{
		if (CheckConsoleSize(_center, _previousCenter, _textArray[_index], _padding, _size)) continue;
		SetCursorPosition(((_center.x + _padding.x) - u_int(_textArray[_index].size())) / 2, (_center.y + (2 * ((_padding.y - _size) / 2 + _index))) / 2);
		printf(_textArray[_index].c_str());
		_previousCenter = _center;
	}
}

void Cursor::Move(Level* _level, const Coords& _offset)
{
	_level->ResetItemAtLocation(position);
	_level->SetItemAtLocation(appearance, position);
}

