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

 

    //TEMP();
    Game _game;

    _game.SelectLevel();
    _game.Start();
    return EXIT_SUCCESS;
}

void SetConsoleName(const string& _name)
{
    SetConsoleTitleA(_name.c_str());
}

void SetConsoleSize(const u_int& _sizeX, const u_int& _sizeY)
{
    HWND Hwnd = GetForegroundWindow();
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    SetWindowLong(Hwnd, GWL_STYLE, (winstyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(Hwnd, HWND_TOP, 0, 0, _sizeX, _sizeY, 0);
}

void MaximizeConsole()
{
    int _x = GetSystemMetrics(SM_CXSCREEN);
    int _y = GetSystemMetrics(SM_CYSCREEN);
    SetConsoleSize(_x, _y);
}

void Config()
{
    (_CrtSetDbgFlag)(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detection de fuite de mémoire
    SetConsoleName("Dwarf Forteress");
    MaximizeConsole();
    InitUTF8;
}


/*
    0 eau profonde
    1 eau peu profonde
    9 haute montagne
*/