#include "MainMenu.h"

MainMenu::MainMenu() : Menu ("Main Menu")
{
	menus =
	{
		new StartMenu(),
		new OptionsMenu(),
		new Menu("Quitter"),
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
	u_int _index = 1;
	cout << "Quelle options choisissez-vous ?" << endl;

	for (const Menu* _menu : menus)
	{
		cout << _index++ << "-" << _menu->GetTitle() << endl;
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
