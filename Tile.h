#pragma once
#include "CoreMinimal.h"
#include "Emoji.h"

static vector<string> emojis = 
{
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

class Tile
{
	int key;

private:
	INLINE bool HasEmoji() const
	{
		return key > 9;
	}
public:
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
	void Display() const;
	string ToString() const;
};