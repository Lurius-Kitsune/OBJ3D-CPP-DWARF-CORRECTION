#include "OptionsMenu.h"

OptionsMenu::OptionsMenu() : Menu("Options")
{
	menus =
	{
		new ControlsMenu(),
		new VideoMenu(),
	};
}

OptionsMenu::~OptionsMenu()
{
	for (const Menu* _menu : menus)
	{
		delete _menu;
	}
}

void OptionsMenu::Show(const bool _toAdd)
{
	Super::Show(_toAdd);

	function<void(const u_int&)> _callback = [&](const u_int& _index) { menus[_index]->Show(); };
	OpenMenu(menus, "Select Options Menu", _callback, false);
}

void OptionsMenu::Interact()
{
	system("cls");
	//menus[currentIndex]->Show();
}