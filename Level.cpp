#include "Level.h"
#include "Cursor.h"
#include "Macro.h"
#include "Color.h"
#include "Emoji.h"
#include "FileStream.h"

Level::Level(const string& _path, const Coords& _coords)
{
	Cursor::GetInstance().SetLocation(_coords);

	path = "Assets/Levels/" + _path + ".txt";
	LoadMap();
	fullMapSize = Size(map);
	view = Size(21, 21);
	biomesData = {
		BiomeData(BT_WATER, {
			TileData(FISH, 10, RT_PERTHOUSAND),
			TileData(SPOUTING_WHALE, 10, RT_PERTHOUSAND),
			TileData(OCTOPUS, 10, RT_PERTHOUSAND),
			TileData(TROPICAL_FISH, 10, RT_PERTHOUSAND),
			TileData(JELLY_FISH, 10, RT_PERTHOUSAND),
		}),
		BiomeData(BT_SAND, {
			TileData(PALM_TREE, 7, RT_PERCENT),
			TileData(CRAB, 1, RT_PERCENT),
			TileData(CROCODILE, 1, RT_PERCENT),
		}),
		BiomeData(BT_GRASS, {
			TileData(TREE, 5, RT_PERCENT),
			TileData(TREE2, 5, RT_PERCENT),
			TileData(FLOWER1, 5, RT_PERTHOUSAND),
			TileData(FLOWER2, 5, RT_PERTHOUSAND),
			TileData(FLOWER3, 5, RT_PERTHOUSAND),
			TileData(FLOWER4, 5, RT_PERTHOUSAND),
			TileData(MONKEY, 5, RT_PERTHOUSAND),
		}),
		BiomeData(BT_DIRT, {
			TileData(ROCK, 3, RT_PERCENT),
		}),
		BiomeData(BT_ROCK, {
			TileData(ROCK, 30, RT_PERCENT),
		}),
		BiomeData(BT_VOLCANO, {
		}),
		BiomeData(BT_LAVA, {
		}),
	};
	displayAll = false;

	//TODO move
	colorSaturation = 1;
	colorBrightness = 1;
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

bool Level::IsValidCoords(const Coords& _coords) const
{
	return _coords.x >= 0 && _coords.x < fullMapSize.x
		&& _coords.y >= 0 && _coords.y < fullMapSize.y;
}

void Level::UpdateSaturation(const double _newValue)
{
	colorSaturation = _newValue;
}

void Level::UpdateBrightness(const double _newValue)
{
	colorBrightness = _newValue;
}

#pragma region Item

bool Level::ChangeItemAtLocation(const Coords& _previousCoords, const string& _appearance, const Coords& _newCoords)
{
	return ResetItemAtLocation(_previousCoords)
		&& SetItemAtLocation(_appearance, _newCoords);
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
	GetTileByCoords(_coords).ResetAppearance();
	return true;
}

void Level::ShowTileInfo()
{
	selectedTile = GetTileByCoords(Cursor::GetInstance().GetLocation());
	selectedTile.ShowInfos();
}

void Level::HideTileInfo()
{
	selectedTile.HideInfos();
}

#pragma endregion

#pragma region Generation

vector<Coords> Level::GetCoordsByBiome(const u_int& _biome) const
{
	vector<Coords> _availablesCoords;

	const u_int& _mapSize = static_cast<const u_int&>(map.size());
	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		const u_int& _rowSize = static_cast<const u_int&>(map[_rowIndex].size());

		for (u_int _columnIndex = 0; _columnIndex < _rowSize - 1; _columnIndex++)
		{
			const Tile& _tile = map[_rowIndex][_columnIndex];
			if (!_tile.HasEmoji() && _tile.GetBackgroundKey() == _biome)
			{
				_availablesCoords.push_back(Coords(_rowIndex, _columnIndex));
			}
		}
	}

	return _availablesCoords;
}

vector<Coords> Level::SelectCoords(vector<Coords> _availablesCooords, const u_int& _percentage, const RateType& _rate) const
{
	const u_int& _coordsCount = static_cast<const u_int&>(_availablesCooords.size());
	shuffle(_availablesCooords.begin(), _availablesCooords.end(), default_random_engine(static_cast<u_int>(chrono::system_clock::now().time_since_epoch().count())));
	const u_int& _coordsCountToSelect = static_cast<const u_int&>(_percentage * _coordsCount / _rate);
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
	for (const BiomeData& _biomeData : biomesData)
	{
		for (const TileData& _tileData : _biomeData.allData)
		{
			const vector<Coords>& _availablesCooords = GetCoordsByBiome(_biomeData.type);
			const vector<Coords>& _selectedCoords = SelectCoords(_availablesCooords, _tileData.percentage, _tileData.rate);
			SpawnAtCoords(_selectedCoords, _tileData.appearance);
		}
	}
	SetupVilage();
}

void Level::SetupVilage()
{
	map[fullMapSize.x / 2][fullMapSize.y / 2].ResetAppearance();
	map[fullMapSize.x / 2][fullMapSize.y / 2].SetAppearance(HUNTER_HUT);
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

void Level::DisplayVerticalBorder(const string& _color, const bool _isRight) const
{
	Print("", _color + "  " + (_isRight ? "\n" : ""), RESET);
}

void Level::DisplayHorizontalBorders(const u_int& _rowSize, const string& _color) const
{
	for (u_int _index = 0; _index < _rowSize + 2; _index++)
	{
		Print("", _color, "  ", RESET);
	}
	Print("\n", RESET);
}

void Level::DisplayMap(const Size& _size, const Coords& _start) const
{
	const u_int& _columnSize = static_cast<const u_int&>(_size.x);
	const u_int& _rowSize = static_cast<const u_int&>(_size.y);
	const string& _borderColor = BG_CYAN;

	DisplayHorizontalBorders(_rowSize, _borderColor);
	for (u_int _columnIndex = 0; _columnIndex < _rowSize; _columnIndex++)
	{
		DisplayVerticalBorder(_borderColor, false);
		for (u_int _rowIndex = 0; _rowIndex < _columnSize; _rowIndex++)
		{
			const u_int& _posX = _columnIndex + _start.x;
			const u_int& _posY = _rowIndex + _start.y;
			const Coords& _currentCoords = Coords(_posX, _posY);
			if (!IsValidCoords(_currentCoords)) continue;
			const bool _isCursor = Cursor::GetInstance().GetLocation() == _currentCoords;
			map[_posX][_posY].Display(_isCursor);
		}
		DisplayVerticalBorder(_borderColor, true);
	}

	DisplayHorizontalBorders(_rowSize, _borderColor);
}

Coords Level::ComputeCenter(const Coords& _coords) const
{
	const Size& _halfView = view / 2;

	const bool _isOutTop = _coords.x - _halfView.x < 0;
	const bool _isOutBottom = _coords.x + _halfView.x >= fullMapSize.x;
	const bool _isOutLeft = _coords.y - _halfView.y < 0;
	const bool _isOutRight = _coords.y + _halfView.y >= fullMapSize.y;

	const int _posX = _isOutBottom ? fullMapSize.x - view.x : _isOutTop ? 0 : _coords.x - _halfView.x;
	const int _posY = _isOutRight ? fullMapSize.y - view.y : _isOutLeft ? 0 : _coords.y - _halfView.y;

	return Coords(_posX, _posY);
}

void Level::DisplayView() const
{
	const Coords& _cursorLocation = Cursor::GetInstance().GetLocation();
	DisplayMap(view, ComputeCenter(_cursorLocation));
}

void Level::DisplayFullMap() const
{
	DisplayMap(fullMapSize);
}

void Level::Display() const
{
	Cursor::GetInstance().SetCursorPosition(0, 0);
	displayAll ? DisplayFullMap() : DisplayView();
}

#pragma endregion