#include "Tile.h"
#include "Color.h"
#include "Macro.h"
#include "Cursor.h"

Tile::Tile(const string& _key)
{
	key = stoi(_key);

	infos = {
		"Ceci est une info !",
		"Oui ?",
		"NON"
	};

	colorBrightness = 1;
	colorSaturation = 1;
}


string Tile::ComputeColor(const bool _isCursorPosition) const
{
	Color _colors[] = {

		Color(0,4,217), // Bleu
		Color(254,255,100), // Jaune
		Color(20,185,20), // Vert
		Color(88,41,0), // Marron
		Color(56,56,56), // Gris
		Color(244,102,27), // Orange 
		Color(255,0,0), // Rouge
	};
	const u_int& _backgroundKey = GetBackgroundKey();
	_colors[_backgroundKey].CalculateSaturation(colorSaturation);
	_colors[_backgroundKey].AdjustBrightness(colorBrightness);

	string _color = _colors[_backgroundKey].ToString(false);
	return _color + (HasEmoji() || _isCursorPosition ? "" : "  " RESET);
}

string Tile::ComputeAppearance() const
{
	const u_int& _forwardKey = GetForwardKey() - 1;
	return emojis[_forwardKey];
}

u_int Tile::GetKeyByAppearance(const string& _appearance) const
{
	u_int _index = 0;

	for (const string& _currentEmoji : emojis)
	{
		if (_currentEmoji == _appearance) return 10 * (_index + 1);
		_index++;
	}

	throw exception("ERROR => Invalid key appearance !");
}

void Tile::SetAppearance(const string& _appearance)
{
	key += GetKeyByAppearance(_appearance);
}

void Tile::ResetAppearance()
{
	key = GetBackgroundKey();
}

void Tile::ShowInfos() const
{
	Cursor _cursor = Cursor::GetInstance();
	Print("", RESET);
	u_int _index = 0;

	for (const string& _info : infos)
	{
		_cursor.SetCursorPosition(75, _index++);
		Print("", _info);
	}
}

void Tile::HideInfos() const
{
	Cursor _cursor = Cursor::GetInstance();
	Print("", RESET);
	u_int _index = 0;
	for (const string& _info : infos)
	{
		_cursor.SetCursorPosition(75, _index++);

		for (const char _letter : _info)
		{
			Print("", " ");
		}
	}
}

void Tile::Display(const bool _isCursor)const
{
	Cursor _cursor = Cursor::GetInstance();
	Print("", ComputeColor(_isCursor));

	if (HasEmoji())
	{
		if (_isCursor)
			Print("", RED_INTENSE_BG);
		Print("", ComputeAppearance(), RESET);
	}
	else if (_isCursor)
		Print("", _cursor.GetAppearance(), RESET);
}

string Tile::ToString() const
{
	return to_string(key);
}