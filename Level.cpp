#include "Level.h"
#include "Macro.h"
#include "FileStream.h"
#include "Emoji.h"

Level::Level(const string& _path, Cursor* _cursor)
{
	savePath = "Asset/Level/" + _path + ".txt";
	LoadMap();
	fullMapSize = Size(map);
	view = Size(35, 35);
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

	//TODO move
	Generate();
}


bool Level::IsOver(const Coords& _coords) const
{
	return false;
}

vector<string> Level::ConvertMapToString() const
{
	vector<string> _mapString;
	const u_int& _rowsCount = static_cast<const u_int&>(map.size());

	for (u_int _rowIndex = 0; _rowIndex < _rowsCount; _rowIndex++)
	{
		const u_int& _columnsCount = static_cast<const u_int&>(map[_rowIndex].size());
		string _rowText;

		for (u_int _columnIndex = 0; _columnIndex < _columnsCount; _columnIndex++)
		{
			_rowText += map[_rowIndex][_columnIndex].ToString();
		}

		_mapString.push_back(_rowText);
	}

	return _mapString;
}

#pragma region Generation

vector<Coords> Level::GetCoordsByBiome(const u_int& _biome) const
{
	for (const BiomeData& _biomesdata : biomesData)
	{
		for (const TileData& _tilesData : _biomesdata.allData)
		{
			const vector<Coords>& _availableCoords = GetCoordsByBiome(_biomesdata.type);
			const vector<Coords> _selectCoords = SelectCoords(_availableCoords, _tilesData.percentage);
			SpawnAtCoords(_selectCoords, _tilesData.appearance);
		}
	}

	//const string& _elementToSpawn = TREE;
	//const u_int& _percentage = 20;
	//const u_int& _biome = 2;
	//const u_int& _coordsCount = static_cast<const u_int&>(_availableCoords.size());
	//SpawnAtCoords(_selectCoords, _elementToSpawn);
}


vector<Coords> Level::GetCoordsByBiome(const u_int& _biome) const
{
	vector<Coords> _availableCoords;

	const u_int& _mapSize = static_cast<const u_int&>(map.size());
	for (int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		vector<Tile> _rowTile;
		const u_int& _rowSize = static_cast<const u_int&>(map[_rowIndex].size());
		for (int _columnIndex = 0; _columnIndex < _rowSize; _columnIndex += 3)
		{
			if (map[_rowIndex][_columnIndex].GetBackgroundKey() == _biome)
			{
				_availablesCoords.push_back(Coords(_rowIndex, _columnIndex));
			}
		}
	}

	return _availableCoords;
}

vector<Coords> Level::SelectCoords(vector<Coords> _availableCoords, const u_int& _percentage) const
{
	const u_int& _coordsCount = static_cast<const u_int&>(_availablesCooords.size());
	random_shuffle(_availablesCooords.begin(), _availablesCooords.end());
	const u_int& _coordsCountToSelect = _percentage * _coordsCount / 100.0f;
	vector<Coords> _selectedCoords;
	_selectedCoords.insert(_selectedCoords.begin(), _availablesCooords.begin(), _availablesCooords.begin() + _coordsCountToSelect);
	return _selectedCoords;
}

void Level::SpawnAtCoords(const vector<Coords>& _selectedCoords, const string& _elementToSpawn)
{
	for (const Coords& _coords : _selectedCoords)
	{
		map[_coords.x][_coords.y].SetAppearance(_elementToSpawn);
	}
}

void Level::Generate()
{
	const string& _elementToSpawn = TREE;
	const u_int& _percentage = 20;
	const u_int& _biome = 2;
	const vector<Coords>& _availablesCooords = GetCoordsByBiome(_biome);
	const vector<Coords>& _selectedCoords = SelectCoords(_availablesCooords, _percentage);
	SpawnAtCoords(_selectedCoords, _elementToSpawn);
}

#pragma endregion

#pragma region Save

void Level::LoadMap()
{
	const vector<string>& _allMap = FileStream::ReadAll(path);
	const u_int& _mapSize = static_cast<const u_int&>(_allMap.size());

	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		vector<Tile> _rowTile;
		const u_int& _rowSize = static_cast<const u_int&>(_allMap[_rowIndex].size());

		for (u_int _columnIndex = 0; _columnIndex < _rowSize - 1; _columnIndex += 3)
		{
			string _tileText;
			for (u_int _index = 0; _index < 3; _index++)
			{
				_tileText += _allMap[_rowIndex][_columnIndex + _index];
			}
			_rowTile.push_back(Tile(_tileText));
		}

		map.push_back(_rowTile);
	}
}
void Level::SaveMap()
{
	FileStream::Write(path, ConvertMapToString());
}
void Level::Save()
{
	SaveMap();
}

#pragma endregion

#pragma region Display

void Level::DisplayMap(const Size& _size, const Coords& _start) const
{
	cursor->SetCursorPosition(0, 0);

	const u_int& _mapSize = static_cast<const u_int&>(_size.x);
	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		const u_int& _rowSize = static_cast<const u_int&>(_size.sizeY);
		for (u_int _columnIndex = 0; _columnIndex < _rowSize; _columnIndex++)
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
	return {
		 _cursorPos.x - view.sizeX / 2,
		 _cursorPos.y - view.sizeY / 2,
	};
}

bool Level::IsValidCoords(const u_int& _rowIndex, const u_int& _columnIndex) const
{
	return _rowIndex >= 0 && _rowIndex < (u_int)fullMapSize.sizeX
		&& _columnIndex >= 0 && _columnIndex < (u_int)fullMapSize.sizeY;
}

void Level::DisplayView(const Coords& _cursorPos) const
{
	DisplayMap(view, ComputeCenter(_cursorPos));
}

void Level::DisplayFullMap() const
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