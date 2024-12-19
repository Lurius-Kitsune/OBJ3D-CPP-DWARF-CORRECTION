#include "MainMenu.h"
#include "StartMenu.h"
#include "OptionsMenu.h"
#include "ControlsMenu.h"
#include "VideoMenu.h"

MainMenu::MainMenu() : Menu("Main")
{
	menus =
	{
		new StartMenu(),
		new OptionsMenu(),
		new ControlsMenu(),
		new VideoMenu(),
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
	system("cls");

	DisplayLogo();
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

void MainMenu::DisplayLogo()
{
	Cursor _cursor;
	Gradient _gradient = Gradient({ 159, 37, 96 }, { 94, 153, 42 });
	ifstream _stream = ifstream("Assets/Logo.txt");
	vector<string> _logo;
	string _line;
	while (getline(_stream, _line)) _logo.push_back(_gradient.GradientString(_line));

	while (!_kbhit()) _cursor.DisplayOnceCenterMultiLine(_logo, (u_int)_logo.size());
}

void MainMenu::Hide()
{
	system("cls");
}