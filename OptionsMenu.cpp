#include "OptionsMenu.h"
#include "ControlsMenu.h"
#include "VideoMenu.h"

OptionsMenu::OptionsMenu(GameInput* _gameInput, Level* _level) : Menu("Options", 2)
{
	menus =
	{
		new ControlsMenu(_gameInput),
		new VideoMenu(_gameInput, _level),
	};
}

OptionsMenu::OptionsMenu(Menu* _parent, GameInput* _gameInput, Level* _level) : Menu("Options", _parent, 2)
{
	menus =
	{
		new ControlsMenu(_gameInput),
		new VideoMenu(_gameInput, _level),
	};
}

OptionsMenu::~OptionsMenu()
{
	for (const Menu* _menu : menus)
	{
		delete _menu;
	}
}

void OptionsMenu::Show()
{
	cout << "Quelle options choisissez-vous ?" << endl;

	u_int _index = 0;
	for (const Menu* _menu : menus)
	{
		cout << (_index == currentIndex ? "> " : "") + _menu->GetTitle() << endl;
		_index++;
	}

	
}

void OptionsMenu::Hide()
{
	system("cls");

	if (owner)
	{
		owner->Show();
	}
}

void OptionsMenu::Interact()
{
	system("cls");
	menus[currentIndex]->Show();
}
