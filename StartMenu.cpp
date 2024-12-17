#include "StartMenu.h"

StartMenu::StartMenu() : Menu("Start")
{
	allSaves = vector<Save>(3);
	allSaves[0] = { "Save1", "coucou" };
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

	Game::SelectLevel(allSaves[_textIndex].path);

}

void StartMenu::Hide()
{
}
