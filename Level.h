#pragma once
#include "CoreMinimal.h"
#include "Size.h"
#include "Cordinates.h"
#include "Color.h"
#include "Cursor.h"
#include "Emoji.h"

class Level
{
	using Map = std::map<char, Color>;

	vector<string> map;
	Size fullMapSize;
	Size viewSize;
	string savePath;
	Cursor* cursor;

public:
	INLINE const Size& GetFullSize()const
	{
		return fullMapSize;
	}

public:
	Level(const string& _path, Cursor* _cursor);

private:

	#pragma region Print
	void DisplayMap(const Size& _size, const Coords& _center = { 0, 0 })const;
	Coords ComputeCenter(const Coords& _cursorPos)const;
	string ComputeColor(const char _letter)const;
	bool IsValidCoords(const u_int& _rowIndex, const u_int& _columnIndex) const;
	#pragma endregion

	#pragma region Save
	void LoadMap();
	string ConvertMapToSave();
	void SaveMap();
	#pragma endregion



public :
	void Save();
	void DisplayView(const Coords& _center);
	void DisplayFullMap();
	bool IsOver(const Coords& _coords) const;
};

