#include "Level.h"
#include "Macro.h"
#include "Filestream.h"

Level::Level(const string& _path, Cursor* _cursor)
{
	savePath = "Asset/Level/" + _path;
	LoadMap();
	fullMapSize = Size(map);
	viewSize = Size(35, 35);
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

void Level::DisplayMap(const Size& _size, const Coords& _start)const
{
	const u_int& _mapSize = static_cast<const u_int&>(_size.sizeX);
	for (u_int _rowIndex = 0; _rowIndex < _mapSize; _rowIndex++)
	{
		const u_int& _rowSize = static_cast<const u_int&>(_size.sizeY);
		for (u_int _columnIndex = 0; _columnIndex < _rowSize ; _columnIndex++)
		{
			const u_int& _posX = _rowIndex + _start.x;
			const u_int& _posY = _columnIndex + _start.y;
			if (!IsValidCoords(_rowIndex, _columnIndex))
			{
				continue;
			}

			const bool _isCursor = cursor->GetCoords() == Coords(_posX, _posY);
			Print(ComputeColor(map[_posX][_posY], _isCursor), false);
			if (_isCursor)
			{
				cout << cursor->GetAppearance();
			}
		}
		cout << endl;
	}
	cout << _start.ToString() << endl;
	cout << cursor->GetCoords().ToString() << endl;
}

Coords Level::ComputeCenter(const Coords& _cursorPos) const
{
	return
	{
		static_cast<int>(_cursorPos.x - viewSize.sizeX / 2),
		static_cast<int>(_cursorPos.y - viewSize.sizeY / 2)
	};
}

string Level::ComputeColor(const char _letter, const bool _isEmoji) const
{
	Map _colors =
	{
		make_pair('#', Color(0,4,217)), // bleu
		make_pair('~', Color(0,156,217)), // bleu clair
		make_pair('%', Color(255,250,112)), // jaune
		make_pair('@', Color(87,189,117)), // vert clair
		make_pair('+', Color(41,207,90)), // vert
		make_pair('-', Color(79,69,49)), // marron clair
		make_pair('=', Color(59,46,21)), // marron
		make_pair(':', Color(41,30,10)), // marron foncé
		make_pair('*', Color(0,0,0)), // noir
	};

	string _color = _colors[_letter].ToString(false);
	return _color + (_isEmoji ? "" : "  ");
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


