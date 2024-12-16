#pragma once
#include "CoreMinimal.h"
#include "Size.h"
#include "Cordinates.h"

class Level
{
	vector<string> MAP;
	Size fullMapSize;
	Size viewSize;

public:
	INLINE const Size& GetFullSize()const
	{
		return fullMapSize;
	}

public:
	Level();

private:
	void DisplayMap(const Size& _size, const Coords& _center = { 0, 0 })const;
	Coords ComputeCenter(const Coords& _cursorPos)const;

public :
	void DisplayView(const Coords& _center);
	void DisplayFullMap();
};

