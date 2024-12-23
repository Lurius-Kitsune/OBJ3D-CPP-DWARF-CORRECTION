#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() : Menu("Start")
{
	allSaves = vector<Save>(3);
}

void StartMenu::LaunchGame(const string& _path)
{
	// load save at path
	const Coords& _cursorLocation = { 109, 200 };
	Level* _level = new Level("MainLevel", _cursorLocation);
	Game::GetInstance().Start(_level);
}

void StartMenu::Show(const bool _toAdd)
{
	const function<void(const u_int&)>& _callback = [&](const u_int& _index) { LaunchGame(allSaves[_index].path); };
	OpenMenu(allSaves, "Quel sauvegarde choisissez-vous ?", _callback);
}