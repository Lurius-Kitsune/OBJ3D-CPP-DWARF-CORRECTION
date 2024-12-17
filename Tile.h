#pragma once
#include "CoreMinimal.h"
#include "Emoji.h"

class Cursor;

static vector<string> emojis = 
{
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

struct TileData
{
	string appearance;
	u_int percentage;

	TileData(const string& _appearance, const u_int& _percentage)
	{
		appearance = _appearance;
		percentage = _percentage;
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

public:
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
	string ComputeColor() const;
	string ComputeAppearance() const;
	u_int GetKeyByAppearance(const string& _appearance) const;

public:
	void SetAppearance(const string& _appearance);
	void ResetAppearance();
	void ShowInfos(Cursor* _cursor) const;
	void HideInfos(Cursor* _cursor) const;
	void Display() const;
	string ToString() const;
};