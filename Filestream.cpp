#include "Filestream.h"

FileStream::FileStream(const string& _fullPath, const ios_base::openmode& _openMode)
{
	openMode = _openMode;
	openMode |= ios_base::binary;
	fullPath = _fullPath;
	stream = fstream(_fullPath, openMode);
}

vector<string> FileStream::ReadAll()
{
	const u_int& _linesCount = ComputeLineOfFile();
	vector<string> _content;
	for (u_int _i = 0; _i < _linesCount; _i++)
	{
		_content.push_back(ReadLine(_i));
	}
	return _content;
}

string FileStream::ReadLine(const u_int& _lineIndex)
{
	if (!IsValid()) return "";

	streampos _position = GetOffset(0, _lineIndex);
	string _content = "";

	stream.seekg(GetOffset(0, _lineIndex));
	getline(stream, _content);
	return _content;
}

streampos FileStream::GetOffset(const u_int& _horizontal, const u_int& _vertical)
{
	u_int _index = 0, _l = 0;
	char _c;
	stream.seekg(0, stream.beg);
	while (_l != _vertical) // Aller à la bonne ligne
	{
		if (stream.get(_c))
		{
			const int _bob = static_cast<const int>(stream.tellg());
			if (_c == '\n') _l++;
			_index++;
		}
		else
		{
			break;
		}
	}
	stream.seekg(_index);
	const streampos& _pos = stream.tellg();

	stream.clear();
	stream.seekg(0, stream.beg);
	return _pos;
}



int FileStream::ComputeLineOfFile()
{
	int _line = 1;
	char _c;
	while (stream.get(_c))
	{
		if (_c == '\n') _line++;
	}
	stream.clear();

	stream.seekg(0, stream.beg);
	return _line;
}