#include "MainMenu.h"
#include "StartMenu.h"
#include "OptionsMenu.h"

MainMenu::MainMenu() : Menu("Main")
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
	cout << "Quelle options choisissez-vous ?" << endl;

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