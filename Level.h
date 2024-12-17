#pragma once
#include "CoreMinimal.h"
#include "Size.h"
#include "Cursor.h"
#include "Coordinates.h"
#include "Tile.h"

class Level
{
	vector<vector<Tile>> map;
	Size fullMapSize;
	Size view;
	string path;
	Cursor* cursor;

public:
	INLINE const Size& GetFullSize() const
	{
		return fullMapSize;
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

	#pragma region Display
private:
	void DisplayMap(const Size& _size, const Coords& _start = Coords()) const;
	Coords ComputeCenter(const Coords& _cursorPos) const;
	bool IsValidCoords(const u_int& _rowIndex, const u_int& _columnIndex) const;

public:
	void DisplayView(const Coords& _cursorPos) const;
	void DisplayFullMap() const;
	#pragma endregion
};