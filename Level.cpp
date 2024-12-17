#include "Level.h"
#include "Macro.h"
#include "Filestream.h"

Level::Level(const string& _path, Cursor* _cursor)
{
	savePath = "Asset/Level/" + _path + ".txt";
	LoadMap();
	fullMapSize = Size(map);
	viewSize = Size(35, 35);
	cursor = _cursor;
	biomesData =
	{
		BiomeData(BT_SAND, {
			TileData(CRAB, 20)
		}),
		BiomeData(BT_GRASS, {
			TileData(TREE, 40),
		})
	};

	Generate();
}

bool Level::IsOver(const Coords& _coords) const
{
	return false;
}

vector<string> Level::ConvertMapToString() const
{
	vector<string> _mapString;

	const u_int& _rowsCount = map.size();
	for (u_int _row = 0; _row < _rowsCount; _row++)
	{
		const u_int& _colsCount = map[_row].size();
		for (u_int _col = 0; _col < _colsCount; _col++)
		{
			_mapString.push_back(map[_row][_col].ToString());
		}
	}

	return _mapString;
}


void Level::Generate()
{
	for (const BiomeData& _biomesdata : biomesData)
	{
		for (const TileData& _tilesData : _biomesdata.allData)
		{
			const vector<Coords>& _availableCoords = GetCoordsByBiome(_biomesdata.type);
			const vector<Coords>& _selectCoords = SelectCoords(_availableCoords, _tilesData.percentage);
			SpawnAtCoords(_selectCoords, _tilesData.appearance);
		}
	}

	//const string& _elementToSpawn = TREE;
	//const u_int& _percentage = 20;
	//const u_int& _biome = 2;
	//const u_int& _coordsCount = static_cast<const u_int&>(_availableCoords.size());
	//SpawnAtCoords(_selectCoords, _elementToSpawn);
}

vector<string> Level::ConvertMapToString() const
{
	return vector<string>();
}

bool Level::IsValidCoords(const u_int& _rowIndex, const u_int& _columnIndex) const
{
	return _rowIndex >= 0 && _rowIndex < (u_int)fullMapSize.sizeX
		&& _columnIndex >= 0 && _columnIndex < (u_int)fullMapSize.sizeY;
}

vector<Coords> Level::GetCoordsByBiome(const u_int& _biome) const
{
	vector<Coords> _availableCoords;

	const u_int& _mapSize = static_cast<const u_int&>(map.size());
	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		vector<Tile> _rowTile;
		const u_int& _rowSize = static_cast<const u_int&>(map[_rowIndex].size());
		for (u_int _columnIndex = 0; _columnIndex < _rowSize; _columnIndex += 3)
		{
			if (map[_rowIndex][_columnIndex].GetBackgroundKey() == _biome)
			{
				_availableCoords.push_back({_rowIndex, _columnIndex});
			}
		}
	}
}

vector<Coords> Level::SelectCoords(const vector<Coords>& _availableCoords, const u_int& _percentage) const
{
	const u_int& _coordsCount = static_cast<const u_int&>(_availableCoords.size());
	random_shuffle(_availableCoords.begin(), _availableCoords.end());

	const u_int& _coordsCountToSelect = _percentage * 100 / _coordsCount;
	return vector<Coords>(_availableCoords.begin(), _availableCoords.begin() + _coordsCountToSelect);

}

void Level::SpawnAtCoords(const vector<Coords>& _selectCoords, const string& _elementToSpawn)
{
	for (const Coords& _coords : _selectCoords)
	{
		map[_coords.x][_coords.y].SetAppearance(_elementToSpawn);
	}
}

void Level::LoadMap()
{

	const vector<string>& _allMap = FileStream::ReadAll(savePath);
	string _tileText;

	const u_int& _mapSize = static_cast<const u_int&>(_allMap.size());
	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		vector<Tile> _rowTile;
		const u_int& _rowSize = static_cast<const u_int&>(_allMap[_rowIndex].size());
		for (u_int _columnIndex = 0; _columnIndex < _rowSize; _columnIndex+=3)
		{
			for (u_int _i = 0; _i < 3; _i++)
			{
				_tileText += _allMap[_rowIndex][_columnIndex + _i];
			}
			_rowTile.push_back(Tile(_tileText));
		}
		map.push_back(_rowTile);

	}
}

void Level::SaveMap()
{

}


bool Level::IsValidCoords(const u_int& _rowIndex, const u_int& _columnIndex) const
{
	return _rowIndex >= 0 && _rowIndex < fullMapSize.sizeX
		&& _columnIndex >= 0 && _columnIndex < fullMapSize.sizeY;
}

void Level::DisplayMap(const Size& _size, const Coords& _start)const
{
	cursor->SetCursorPosition(0, 0);

	const u_int& _mapSize = static_cast<const u_int&>(_size.sizeX);
	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		const u_int& _rowSize = static_cast<const u_int&>(_size.sizeY);
		for (u_int _columnIndex = 0; _columnIndex < _rowSize ; _columnIndex++)
		{
			const u_int& _posX = _rowIndex + _start.x;
			const u_int& _posY = _columnIndex + _start.y;

			if (!IsValidCoords(Coords(_posX, _posY)))continue;
			map[_posX][_posY].Display();

			//const bool _isCursor = cursor->GetCoords() == Coords(_posX, _posY);

			/*string _tileText;
			for (u_int _i = 0; _i < 3; _i++)
			{
				_tileText += map[_posX + _i][_posY].ToString();
			}
			Tile(_tileText).Display();*/

			/*if (_isCursor)
			{
				cout << cursor->GetAppearance();
			}*/
		}
		cout << endl;
	}
	/*cout << _start.ToString() << endl;
	cout << cursor->GetCoords().ToString() << endl;*/
}

Coords Level::ComputeCenter(const Coords& _cursorPos) const
{
	return
	{
		static_cast<int>(_cursorPos.x - viewSize.sizeX / 2),
		static_cast<int>(_cursorPos.y - viewSize.sizeY / 2)
	};
}


void Level::Save()
{
	SaveMap();
}

void Level::DisplayView(const Coords& _coords)
{
	DisplayMap(viewSize, ComputeCenter(_coords));
}

void Level::DisplayFullMap()
{
	DisplayMap(fullMapSize);
}

bool Level::SetItemAtLocation(const string& _appearance, const Coords& _coords)
{
	if (!IsValidCoords(_coords)) return false;
	
	GetTileByCoords(_coords).SetAppearance(_appearance);
	return true;
}

bool Level::ResetItemAtLocation(const Coords& _coords)
{
	if (!IsValidCoords(_coords)) return false;
	GetTileByCoords(_coords).SetAppearance(" "); //TODO METTRE EMPTY

}