#include "Main.h"
#include "Macro.h"
#include "Animation.h"
#include "Game.h"
#include "FileStream.h"

/* TODO list
* 
* Menu
* View
* Setup village
* Setup items
* Cacher/Dévoiler carte
* Save carte avec item et zone dévoilée
* 
*/

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
	const u_int& _end = 0xFFFFFF;

    for (u_int _index = _start; _index < _end; _index++)
    {
        if (_kbhit()) break;

        const string& _emoji = ComputeEmoji(_index);
        Print("", _emoji);
        SLEEP(milliseconds, 50);
        system("cls");
    }
}

struct MyStruct
{
    void A() {}
};

int main()
{
	DefaultSetup();

    /*vector<string> _map = FileStream::ReadAll("Assets/Levels/MainLevel/.txt");
    vector<string> _newMap;

    for (size_t i = 0; i < _map.size(); i++)
    {
        _newMap.push_back();
        for (size_t j = 0; j < _map[i].size(); j++)
        {
            for (size_t k = 0; k < 2; k++)
            {
                _newMap[i].push_back('0');
            }
            _newMap[i][j]
        }
    }
    FileStream::Write("Assets/Levels/MainLevel/.txt", _map);
    return -1;*/

	//TEMP();
    // TODO teste after animation
    //Animation _anim;
    //_anim.LoadStartUpAnimation(".\\Assets\\LoadingScreen\\ALS-", ".txt", 44);

    // Main menu -> Start / Options / Quit
    // Start => Créer / Reprendre
    // Options => Audio / Controls / Video
    // Audio => Volume / Dwarf / Attackers / Animals / Environment
    // Controls => Affichage clavier / souris
    // Video => Intensity / Framerate / Daltonien / etc..
    // Quit => quitter

    Game _game;
    _game.SelectLevel("MainLevel");
    _game.Start();

	return EXIT_SUCCESS;
}

void DefaultSetup()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    SetConsoleName("Dwarf Fortress");
    SetConsoleSize(1200, 800);
	InitUTF8;
}

void SetConsoleName(const string& _consoleName)
{
    SetConsoleTitleA(_consoleName.c_str());
}

void SetConsoleSize(const u_int& _sizeX, const u_int& _sizeY)
{
    const HWND& _hwnd = GetForegroundWindow();
    const LONG& _winstyle = GetWindowLong(_hwnd, GWL_STYLE);
    //SetWindowLong(_hwnd, GWL_STYLE, (_winstyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(_hwnd, HWND_TOP, 0, 0, _sizeX, _sizeY, 0);
}

void MaximizeConsole()
{
    const int _x = GetSystemMetrics(SM_CXSCREEN);
    const int _y = GetSystemMetrics(SM_CYSCREEN);
    SetConsoleSize(_x, _y);
}