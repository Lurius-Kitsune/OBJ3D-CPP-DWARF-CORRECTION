#include "MainMenu.h"
#include "StartMenu.h"
#include "OptionsMenu.h"
#include "ControlsMenu.h"
#include "VideoMenu.h"

MainMenu::MainMenu(GameInput* _gameInput, Level* _level) : Menu("Main", 4)
{
	menus =
	{
		new StartMenu(),
		new OptionsMenu(_gameInput, _level),
		new ControlsMenu(_gameInput),
		new VideoMenu(_gameInput, _level),
		new Menu("Quitter", 0),
	};
}

MainMenu::~MainMenu()
{
	for (const Menu* _menu : menus)
	{
		delete _menu;
	}
}


void MainMenu::Show()
{
	system("cls");

	cout << "Quelle option choisissez-vous ?" << endl;

	u_int _index = 1;
	for (const Menu* _menu : menus)
	{
		cout << _index++ << " - " << _menu->GetTitle() << endl;
	}

	u_int _textIndex;
	cin >> _textIndex;
	_textIndex--;

	menus[_textIndex]->Show();
}

void MainMenu::Hide()
{
	system("cls");
}