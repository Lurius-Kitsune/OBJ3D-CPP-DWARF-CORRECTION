#pragma once
#include "CoreMinimal.h"
#include "Size.h"
#include "Cordinates.h"

class Level
{
	vector<string> map;
	Size fullMapSize;
	Size viewSize;
	string savePath;

public:
	INLINE const Size& GetFullSize()const
	{
		return fullMapSize;
	}

public:
	Level(const string& _path);

private:
	void DisplayMap(const Size& _size, const Coords& _center = { 0, 0 })const;
	Coords ComputeCenter(const Coords& _cursorPos)const;

public :
	void LoadMap();
	string ConvertMapToString();
	void SaveMap();
	void DisplayView(const Coords& _center);
	void DisplayFullMap();
};

