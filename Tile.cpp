#include "Tile.h"

Tile::Tile(const string& _key)
{
    key = _key;
    keyValue = stoi(key);
    emojis = 
    {
        CROSSHAIRE,
        CROSSHAIRE2,
        VILLAGE_EMOJI,
        HOUSE_EMOJI,
        FORGE_EMOJI,
        HUNTER_HUT_EMOJI,
        MONUMENT_EMOJI,
        LOVE_HOUSE_EMOJI,
        FARM_EMOJI,
        TREE_TYPE1_EMOJI,
        TREE_TYPE2_EMOJI,
        TREE,
        STONE_EMOJI,
        FOOD_EMOJI,
        WOOD_EMOJI,
        WATER_EMOJI,
        DWARF_EMOJI,
        ENEMY_EMOJI,
        ANIMAL_EMOJI,
        SPIRAL_SHELL,
        CRAB,
        TIGER,
        LION,
        PALM_TREE,
        FOOTSTEP,
        WOLF,
        BOAR,
        FISH,
        CROSSHAIR_EMOJI,
        MONKEY_EMOJI,
        FOOT_EMOJI,
        SANTA_CLAUS_EMOJI,
        TREE1,
        TREE2,
        TREX,
        DEAD,
        GEMSTONE,
        CROCODILE,
        PARROT,
        GORILLA,
        OTTER,
        MOON,
        SUN,
        MEAT
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
        if (_emoji == _appearance) return _index;
        _index++;
    }

    throw exception("ERROR => Invalid key for appearance");
}

void Tile::SetAppearance(const string& _appearance)
{
    key = GetKeyByAppearance(_appearance);
}
