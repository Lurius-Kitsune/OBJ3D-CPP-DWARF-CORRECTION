#pragma once
#include "CoreMinimal.h"
#include "Emoji.h"

class Cursor;

static vector<string> emojis = {
	CROSSHAIR,
	VILLAGE,
	HOUSE,
	FORGE,
	MONUMENT,
	HUNTER_HUT,
	LOVE_HOUSE,
	TRACTOR,
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
	SPOUTING_WHALE,
	OCTOPUS,
	TROPICAL_FISH,
	JELLY_FISH,
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
	FOOTSTEP
};

enum BiomeType
{
	BT_WATER,
	BT_SAND,
	BT_GRASS,
	BT_DIRT,
	BT_ROCK,
	BT_VOLCANO,
	BT_LAVA,

	BT_COUNT
};

enum RateType
{
	RT_PERTEN = 10,
	RT_PERCENT = 100,
	RT_PERTHOUSAND = 1000,
};

struct TileData
{
	string appearance;
	u_int percentage;
	RateType rate;

	TileData(const string& _appearance, const u_int& _percentage, const RateType& _rate)
	{
		appearance = _appearance;
		percentage = _percentage;
		rate = _rate;
	}
};

struct BiomeData
{
	BiomeType type;
	vector<TileData> allData;

	BiomeData(const BiomeType& _type, const vector<TileData>& _allData)
	{
		type = _type;
		allData = _allData;
	}
};

class Tile
{
	int key;
	vector<string> infos;
	double colorSaturation;
	double colorBrightness;

public:
	INLINE void SetColorSaturation(const int _value)
	{
		colorSaturation = _value;
	}

	INLINE void SetColorBrightness(const int _value)
	{
		colorBrightness = _value;
	}
	INLINE bool IsValid() const
	{
		return !HasEmoji();
	}
	INLINE bool HasEmoji() const
	{
		return key > 9;
	}
	INLINE u_int GetBackgroundKey() const
	{
		return key % 10;
	}
	INLINE u_int GetForwardKey() const
	{
		return key / 10;
	}

public:
	Tile() = default;
	Tile(const string& _key);

private:
	string ComputeColor(const bool _isCursorPosition) const;
	string ComputeAppearance() const;
	u_int GetKeyByAppearance(const string& _appearance) const;

public:
	void SetAppearance(const string& _appearance);
	void ResetAppearance();
	void ShowInfos() const;
	void HideInfos() const;
	void Display(const bool _isCursor) const;
	string ToString() const;
};