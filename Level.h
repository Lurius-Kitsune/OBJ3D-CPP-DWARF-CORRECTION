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
	bool displayAll;
	double colorSaturation;
	double colorBrightness;

public:
	INLINE vector<vector<Tile>> GetMap() const
	{
		return map;
	}
	INLINE const Size& GetFullSize() const
	{
		return fullMapSize;
	}
	INLINE const double GetColorSaturation() const
	{
		return colorSaturation;
	}

private:
	INLINE Tile& GetTileByCoords(const Coords& _coords)
	{
		return map[_coords.x][_coords.y];
	}

public:
	Level(const string& _path, const Coords& _coords);

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
	bool ChangeItemAtLocation(const Coords& _previousCoords, const string& _appearance, const Coords& _newCoords);
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
	void DisplayVerticalBorder(const string& _color, const bool _isRight) const;
	void DisplayHorizontalBorders(const u_int& _rowSize, const string& _color) const;
	void DisplayMap(const Size& _size, const Coords& _start = Coords()) const;
	Coords ComputeCenter(const Coords& _coords) const;
	void DisplayView() const;
	void DisplayFullMap() const;

public:
	void Display() const;
	#pragma endregion
};