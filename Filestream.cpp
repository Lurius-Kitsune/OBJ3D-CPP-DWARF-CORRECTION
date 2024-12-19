#include "FileStream.h"
#include "Color.h"
#include "Cursor.h"

vector<string> FileStream::ReadAll(const string& _path) 
{
	const openMode& _openMode = ios_base::in | ios_base::binary;
	ifstream _stream(_path, _openMode);
	vector<string> _lines;
	string _line;

	while (getline(_stream, _line))
	{
		_lines.push_back(_line);
	}

	return _lines;
}

bool FileStream::Write(const string& _path, const vector<string>& _content)
{
	const openMode& _openMode = ios_base::out | ios_base::binary;
	ofstream _myStream(_path, _openMode);

	if (_myStream)
	{
		const u_int& _rowsCount = static_cast<const u_int&>(_content.size());
		for (u_int _rowIndex = 0; _rowIndex < _rowsCount; _rowIndex++)
		{
			const u_int& _columnsCount = static_cast<const u_int&>(_content[_rowIndex].size());
			for (u_int _columnIndex = 0; _columnIndex < _columnsCount; _columnIndex++)
			{
				_myStream << _content[_rowIndex][_columnIndex];
			}

			_myStream << "\n";
		}
	}

	else
	{
		cout << "Error => this file cannot be opened !" << endl;
		return false;
	}

	return true;
}

void FileStream::DisplayFile(const string& _path, const Gradient& _color)
{
	Cursor _cursor;
	ifstream _stream = ifstream(_path);


	vector<string> _logo;
	string _line;
	while (getline(_stream, _line))
	{
		_logo.push_back(_color.GradientString(_line));
	}

	while (!_kbhit())
	{
		_cursor.DisplayOnceCenterMultiLine(_logo, CAST(u_int,_logo.size()));
	}
}
