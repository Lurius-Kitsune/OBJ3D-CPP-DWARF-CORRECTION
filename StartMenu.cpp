#include "StartMenu.h"
#include "Game.h"

StartMenu::StartMenu() : Menu("Start")
{
	allSaves = vector<Save>(3);
	allSaves[0] = Save("Save1", "coucou");
}

void StartMenu::Show()
{
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