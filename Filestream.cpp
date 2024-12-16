#include "Filestream.h"

FileStream::FileStream(const string& _fullPath, const bool _autoCreate,
    const string& _cryptageKey, const bool _isCrypt,
    const ios_base::openmode& _openMode)
{
    openMode = _openMode;
    openMode |= ios_base::binary;
    fullPath = _fullPath;
    isCrypt = _isCrypt;
    cryptageKey = _cryptageKey;
    cryptageKeySize = static_cast<u_int>(cryptageKey.size());
    if (_autoCreate)
    {
        ifstream(_fullPath, ios_base::app);
    }
    stream = fstream(_fullPath, openMode);
}

vector<string> FileStream::ReadAll(const string& _path)
{
    const ios_base::openmode& _openMode = ios_base::in | ios_base::binary;
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
    const ios_base::openmode& _openMode = ios_base::out | ios_base::binary;
    ofstream _myStream(_path, _openMode);

    if (_myStream)
    {
        const u_int& _rowsCount = static_cast<const u_int&>(_content.size());
        for (u_int _rowIndex = 0; _rowIndex < _rowsCount; _rowIndex++)
        {
            const u_int& _columnsCount = static_cast<const u_int&>(_content.size());
            for (u_int _columnIndex = 0; _columnIndex < _columnsCount; _columnIndex++)
            {
                _myStream << _content[_rowIndex][_columnIndex];
            }

            _myStream << "\n";
        }
    }

    else
    {
        cout << "ERREUR => This file cannot be loaded !" << endl;
    }

    return true;
}