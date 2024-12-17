#include "Tile.h"

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
    const Color _colors[] =
    {
        Color(0,4,217),
        Color(254,255,100),
        Color(20,185,20),
        Color(88,41,0),
        Color(56,56,56),
        Color(244,102,27),
        Color(255,0,0),
    };

    const u_int& _backgroundKey = keyValue % 10;
    string _color = _colors[_backgroundKey].ToString(false);
    return _color += HasEmoji() ? "" : " ";
}

string Tile::ComputeAppearance() const
{
    if (!HasEmoji()) return "";
    

    const u_int& _forwardKey = keyValue / 10 - 1;
    return emojis[_forwardKey];
}

void Tile::Display() const
{
    Print("", ComputeColor());
    if (HasEmoji()) Print("", ComputeAppearance());
}

string Tile::ToString() const
{
    return to_string(keyValue);
}

u_int Tile::GetKeyByAppearance(const string& _appearance) const
{
    u_int _index = 0;
    for (const string& _emoji : emojis)
    {
        if (_emoji == _appearance) return _index + 1;
        _index++;
    }

    throw exception("ERROR => Invalid key for appearance");
}

void Tile::SetAppearance(const string& _appearance)
{
    key += 10 * GetKeyByAppearance(_appearance);
}
