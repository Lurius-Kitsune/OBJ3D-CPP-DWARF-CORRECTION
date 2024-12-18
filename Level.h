#pragma once
#include "CoreMinimal.h"
#include "Size.h"
#include "Coordinates.h"
#include "Tile.h"

class Cursor;

class Level
{
	vector<vector<Tile>> map;
	Size fullMapSize;
	Size view;
	string path;
	vector<BiomeData> biomesData;
	Tile selectedTile;
	bool displayAll = false;
	double colorSaturation;
	double colorBrightness;

public:
	INLINE const Size& GetFullSize() const
	{
		return fullMapSize;
	}

	INLINE const double GetColorSaturation() const
	{
		return colorSaturation;
	}

	INLINE bool GetDisplayAll() const
	{
		return displayAll;
	}

	void SetDisplayAll(const bool _displayAll)
	{
		displayAll = _displayAll;
	}

private:
	INLINE Tile& GetTileByCoords(const Coords& _coords)
	{
		return map[_coords.x][_coords.y];
	}


public:
	Level(const string& _path, const Coords& _coord);

public:
	bool IsOver(const Coords& _coords) const;
	bool IsValidCoords(const Coords& _coords) const;
private:
	vector<string> ConvertMapToString() const;

public:
	void UpdateSaturation(const double _newValue);
	void UpdateBrightness(const double _newValue);

#pragma region Item
public:
	bool SetItemAtLocation(const string& _appearance, const Coords& _coords);
	bool ResetItemAtLocation(const Coords& _coords);
	void ShowTileInfo();
	void HideTileInfo();
#pragma endregion

#pragma region Generation
private:
	vector<Coords> GetCoordsByBiome(const u_int& _biome) const;
	vector<Coords> SelectCoords(vector<Coords> _availablesCooords, const u_int& _percentage, const RateType& _rate) const;

	void SpawnAtCoords(const vector<Coords>& _selectedCoords, const string& _elementToSpawn);

	void SetupVilage();
public:
	void Generate();
#pragma endregion

#pragma region Save
private:
	void LoadMap();
	//string ConvertMapToSave();
	void SaveMap();

public:
	void Save();
#pragma endregion

#pragma region Display
private:
	void DisplayMap(const Size& _size, const Coords& _start = Coords())const;
	Coords ComputeCenter(const Coords& _cursorPos) const;
	void DisplayHorizontalBorder(const u_int& _rowSize) const;
	void DisplayVerticalBorder(const string& _color, const bool _isRight) const;

public:
	void DisplayView(const Coords& _cursorPos)const;
	void DisplayFullMap()const;
#pragma endregion

public:
	void Display() const;
};