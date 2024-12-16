#include "Main.h"

string ComputeEmoji(int _codePoint)
{
    string _result;

    if (_codePoint <= 0x7F)
    {
        _result += static_cast<char>(_codePoint);
    }
    else if (_codePoint <= 0x7FF)
    {
        _result += static_cast<char>(0xC0 | ((_codePoint >> 6) & 0x1F));
        _result += static_cast<char>(0x80 | (_codePoint & 0x3F));
    }
    else if (_codePoint <= 0xFFFF)
    {
        _result += static_cast<char>(0xE0 | ((_codePoint >> 12) & 0x0F));
        _result += static_cast<char>(0x80 | ((_codePoint >> 6) & 0x3F));
        _result += static_cast<char>(0x80 | (_codePoint & 0x3F));
    }
    else if (_codePoint <= 0x10FFFF)
    {
        _result += static_cast<char>(0xF0 | ((_codePoint >> 18) & 0x07));
        _result += static_cast<char>(0x80 | ((_codePoint >> 12) & 0x3F));
        _result += static_cast<char>(0x80 | ((_codePoint >> 6) & 0x3F));
        _result += static_cast<char>(0x80 | (_codePoint & 0x3F));
    }

    return _result;
}

void TEMP()
{
    const u_int& _start = 0x1F600;
    const u_int& _end = 0xFFFFF;

    for (u_int _index = 0x1F600; _index < _end; _index++)
    {
        if (_kbhit()) break;
        const string& _emoji = ComputeEmoji(_index);
        cout << _emoji << " " << hex << uppercase << "U+" << _index << endl;
        SLEEP(milliseconds, 50);
        //CLEAR_SCREEN;
    }
}

int main()
{
    Config();

    TEMP();
    const string& _path = "Asset/Map/DefaultLevel.txt";
    Level _level = Level(_path);

    _level.DisplayFullMap();

    const Size& _center = _level.GetFullSize() / 2.0f;
    _level.DisplayView(Coords(_center));
    _level.Save();
    return EXIT_SUCCESS;
}

void Config()
{
    (_CrtSetDbgFlag)(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detection de fuite de mémoire
    InitUTF8;
}


/*
    0 eau profonde
    1 eau peu profonde
    9 haute montagne
*/