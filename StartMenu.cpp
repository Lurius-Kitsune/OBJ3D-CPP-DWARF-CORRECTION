#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() : Menu("Start")
{
	allSaves = vector<Save>(3);
}

void StartMenu::LaunchGame(const string& _path)
{
	const Coords& _cursorLocation = { 109, 200 };
	Level* _level = new Level("MainLevel", _cursorLocation);
	Game::GetInstance().Start(_level);
}

void StartMenu::Show(const bool _toAdd)
{
	function<void(const u_int&)> _callback = [&](const u_int& _index) { LaunchGame(allSaves[_index].path); };
	OpenMenu(allSaves, "Quel sauvegarde choisissez-vous ?", _callback, false);

	u_int _index = 0;
	for (const Save& _save : allSaves)
	{
		cout << _index++ << " - " << _save.title << endl;
	}

	u_int _textIndex;
	cin >> _textIndex;
	_textIndex--;
}

void StartMenu::Hide()
{

}