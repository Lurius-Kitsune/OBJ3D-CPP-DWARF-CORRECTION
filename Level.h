#pragma once
#include "CoreMinimal.h"
#include "Size.h"
#include "Cursor.h"
#include "Cordinates.h"
#include "Tile.h"

class Level
{
	vector<vector<Tile>> map;
	Size fullMapSize;
	Size view;
	string path;
	Cursor* cursor;
	vector<BiomeData> biomesData;

public:
	INLINE const Size& GetFullSize() const
	{
		return fullMapSize;
	}
private:
	INLINE Tile& GetTileByCoords(const Coords& _coords)
	{
		return map[_coords.x][_coords.y];
	}


public:
	Level(const string& _path, Cursor* _cursor);

public:
	bool IsOver(const Coords& _coords) const;
private:
	vector<string> ConvertMapToString() const;

#pragma region Generation
private:
	vector<Coords> GetCoordsByBiome(const u_int& _biome) const;
	vector<Coords> SelectCoords(vector<Coords> _availablesCooords, const u_int& _percentage) const;

	void SpawnAtCoords(const vector<Coords>& _selectedCoords, const string& _elementToSpawn);

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

	vector<Coords> GetCoordsByBiome(const u_int& _biome) const;
	vector<Coords> SelectCoords(vector<Coords> _availableCoords, const u_int& _percentage) const;
	void SpawnAtCoords(const vector<Coords> _selectCoords, const string& _elementToSpawn);

	vector<string> ConvertMapToString() const;

public :
	
	void Save();
	void DisplayView(const Coords& _coords);
	void DisplayFullMap();
	bool IsOver(const Coords& _coords) const;
	void Generate();
public:

	bool SetItemAtLocation(const string& _appearance, const Coords& _coords);
	bool ResetItemAtLocation(const Coords& _coords);
};

