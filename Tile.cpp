#include "Tile.h"
#include "Color.h"
#include "Macro.h"

Tile::Tile(const string& _key)
{
	key = stoi(_key);
    emojis =
    {
        VILLAGE,
        HOUSE,
        FORGE,
        MONUMENT,
        HUNTER_HUT,
        LOVE_HOUSE,
        TRACTOR,
        FARM_EMOJI,
        ANIMAL,
        WOLF,
        BOAR,
        FISH,
        MONKEY,
        CRAB,
        TIGER,
        LION,
        CROCODILE,
        PARROT,
        GORILLA,
        WATER,
        TREE,
        TREE2,
        PALM_TREE,
        GRASS,
        WIND,
        FLOWER1,
        FLOWER2,
        FLOWER3,
        FLOWER4,
        ROCK,
        FOOD,
        LOG,
        MEAT,
        DWARF,
        ENEMY,
        FOOTSTEP,
    };
}


string Tile::ComputeColor() const
{
	const Color _colors[] = {

		Color(0,4,217), // Bleu
		Color(254,255,100), // Jaune
		Color(20,185,20), // Vert
		Color(88,41,0), // Marron
		Color(56,56,56), // Gris
		Color(244,102,27), // Orange 
		Color(255,0,0), // Rouge
	};
	const u_int& _backgroundKey = GetBackgroundKey();
	string _color = _colors[_backgroundKey].ToString(false);
	return _color += HasEmoji() ? "" : "  ";
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
		if (_currentEmoji == _appearance) return _index + 1;
		_index++;
	}

	throw exception("ERROR => Invalid key appearance !");
}

void Tile::SetAppearance(const string& _appearance)
{
	key += 10 * GetKeyByAppearance(_appearance);
}

void Tile::Display() const
{
    u_int _index = 0;
    for (const string& _emoji : emojis)
    {
        if (_emoji == appearance) return _index + 1;
        _index++;
    }

    throw exception("ERROR => Invalid key for appearance");
}

string Tile::ToString() const
{
    key += 10 * GetKeyByAppearance(_appearance);
}

void Tile::ShowInfo(Cursor* _cursor) const
{
    
    u_int _index = 0;
    for (const string& _info : infos)
    {
        _cursor->SetCursorPosition(75, _index++);
        Print("", _info);
    }
}

void Tile::HideInfo(Cursor* _cursor) const
{
    u_int _index = 0;
    for (const string& _info : infos)
    {
        _cursor->SetCursorPos(75, _index++);

        for (const char _letter : _info)
        {
            Print("", " ");
        }
    }
}

