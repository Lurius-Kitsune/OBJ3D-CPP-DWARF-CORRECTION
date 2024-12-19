#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() : Menu("Start")
{
	allSaves = vector<Save>(3);
	allSaves[0] = Save("Save1", "MainLevel");
}

void StartMenu::LaunchGame(const string& _path)
{
	// Load Save Path
	Level* _level = new Level(_path);
	Game::GetInstance().Start(_level);
}

void StartMenu::Show(const bool _toAdd)
{
	function<void(const u_int&)> _callback = [&](const u_int& _index) { LaunchGame(allSaves[_index].path); };
	OpenMenu(allSaves, "Quel sauvegarde choisissez-vous ?", _callback, false);
}

void StartMenu::Hide()
{

}