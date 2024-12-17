#pragma once
#include "CoreMinimal.h"
#include "Emoji.h"
#include "Macro.h"
#include "Color.h"

enum BiomeType
{
    BT_WATER,
    BT_SAND,
    BT_GRASS,
    BT_DIRT,
    BT_ROCK,
    BT_LAVA,

    BT_COUNT
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



class Tile
{
    string key;
    int keyValue;
    vector<string> emojis;

private:
    INLINE bool HasEmoji() const
    {
        return keyValue > 9;
    }

public:
    INLINE u_int GetBackgroundKey() const
    {
        return keyValue % 10;
    }

    INLINE u_int GetForwardKey() const
    {
        return keyValue / 10;
    }

public:
    Tile(const string& _key);

private:
    string ComputeColor() const;
    string ComputeAppearance() const;
    u_int GetKeyByAppearance(const string& _appearance) const;

public:
    void Display() const;
    string ToString() const;

    void SetAppearance(const string& _appearance);

};

