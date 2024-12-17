#pragma once
#include "CoreMinimal.h"
#include "Size.h"
#include "Cordinates.h"
#include "Color.h"
#include "Cursor.h"
#include "Emoji.h"
#include "Tile.h"


class Level
{
	using Map = std::map<char, Color>;

	vector<vector<Tile>> map;
	Size fullMapSize;
	Size viewSize;
	string savePath;
	Cursor* cursor;
	vector<BiomeData> biomesData;

public:
	INLINE const Size& GetFullSize()const
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

private:

	#pragma region Print
	void DisplayMap(const Size& _size, const Coords& _start = { 0, 0 })const;
	Coords ComputeCenter(const Coords& _cursorPos)const;
	bool IsValidCoords(const u_int& _rowIndex, const u_int& _columnIndex) const;
	#pragma endregion

	#pragma region Save
	void LoadMap();
	void SaveMap();
	#pragma endregion

	vector<Coords> GetCoordsByBiome(const u_int& _biome) const;
	vector<Coords> SelectCoords(const vector<Coords>& _availableCoords, const u_int& _percentage) const;
	void SpawnAtCoords(const vector<Coords>& _selectCoords, const string& _elementToSpawn);

	vector<string> ConvertMapToString() const;

public :
	
	void Save();
	void DisplayView(const Coords& _coords);
	void DisplayFullMap();
	bool IsOver(const Coords& _coords) const;
	void Generate();

private:
	vector<string> ConvertMapToString() const;
	bool IsValidCoords(const Coords& _coords) const ;
public:

	bool SetItemAtLocation(const string& _appearance, const Coords& _coords);
	bool ResetItemAtLocation(const Coords& _coords);
};

