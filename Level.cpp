#include "Level.h"
#include "Macro.h"
#include "Filestream.h"

Level::Level(const string& _path, Cursor* _cursor)
{
	savePath = "Asset/Level/" + _path;
	LoadMap();
	fullMapSize = Size(map);
	viewSize = Size(21, 21);
	cursor = _cursor;
}

bool Level::IsOver(const Coords& _coords) const
{
	return false;
}


void Level::LoadMap()
{
	vector<string> _map = FileStream::ReadAll(savePath);

	map = _map;

}

string Level::ConvertMapToSave()
{
	const u_int& _mapSize = static_cast<const u_int&>(fullMapSize.sizeX);
	string _content = "";
	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		const u_int& _rowSize = static_cast<const u_int&>(fullMapSize.sizeY);
		_content += "-" + map[_rowIndex];
		_content += "\n";
	}
	return _content;
}

void Level::SaveMap()
{
	//FileStream _stream = FileStream(savePath, true);
	ofstream _myStream(savePath);

	if (_myStream)
	{
		const u_int& _mapSize = static_cast<const u_int&>(fullMapSize.sizeX);
		string _content = "";
		for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
		{
			const u_int& _rowSize = static_cast<const u_int&>(fullMapSize.sizeY);
			_myStream << map[_rowIndex] << "\n";
		}
	}
	else
	{
		cout << "Cant open File" << endl;
	}
}

bool Level::IsValidCoords(const u_int& _rowIndex, const u_int& _columnIndex) const
{
	return _rowIndex >= 0 && _rowIndex < fullMapSize.sizeX
		&& _columnIndex >= 0 && _columnIndex < fullMapSize.sizeY;
}

void Level::DisplayMap(const Size& _size, const Coords& _center)const
{
	const u_int& _mapSize = static_cast<const u_int&>(_size.sizeX);
	for (u_int _rowIndex = _center.x; _rowIndex < _center.x + _mapSize; _rowIndex++)
	{
		const u_int& _rowSize = static_cast<const u_int&>(_size.sizeY);
		for (u_int _columnIndex = _center.y; _columnIndex < _center.y + _rowSize ; _columnIndex++)
		{
			if (!IsValidCoords(_rowIndex, _columnIndex))
			{
				continue;
			}
			if (cursor->GetCoords() == Coords(_rowIndex, _columnIndex))
			{
				Print(ComputeColor(map[_rowIndex][_columnIndex]) + cursor->GetAppearance() + " ", false);
			}
			else
			{
				Print(ComputeColor(map[_rowIndex][_columnIndex]) + "  ", false);
			}
		}
		cout << endl;
	}
}

Coords Level::ComputeCenter(const Coords& _cursorPos) const
{
	return
	{
		static_cast<int>(_cursorPos.x - viewSize.sizeX / 2.0f),
		static_cast<int>(_cursorPos.y - viewSize.sizeY / 2.0f)
	};
}

string Level::ComputeColor(const char _letter) const
{
	Map _colors =
	{
		make_pair('*', Color(0,0,0)),
		make_pair(':', Color(41,30,10) ),
		make_pair('=', Color(50,46,21) ),
		make_pair('-', Color(79,69,49) ),
		make_pair('+', Color(41,207,90) ),
		make_pair('@', Color(87,189,117) ),
		make_pair('%', Color(255,250,112) ),
		make_pair('~', Color(0,156,217) ),
		make_pair('#', Color(0,4,217))
	};

	return _colors[_letter].ToString(false) ;
}

void Level::Save()
{
	SaveMap();
}

void Level::DisplayView(const Coords& _cursorPos)
{
	DisplayMap(viewSize, ComputeCenter(_cursorPos));
}

void Level::DisplayFullMap()
{
	DisplayMap(fullMapSize);
}


