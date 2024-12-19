#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() : Menu("Start")
{
	allSaves = vector<Save>(3);
	allSaves[0] = Save("Save1", "coucou");
}

void StartMenu::LaunchGame(const string& _path)
{
	//TODO start game
}

void StartMenu::Show(const bool _toAdd)
{
	const function<void(const u_int&)> _callback = [&](const u_int& _index) { allSaves[_index]; };
	OpenMenu(allSaves, "Quelle sauvegarde choisissez-vous ?", _callback);
}