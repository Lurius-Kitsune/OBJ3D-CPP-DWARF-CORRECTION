#include "MainMenu.h"
#include "StartMenu.h"
#include "OptionsMenu.h"
#include "ControlsMenu.h"
#include "VideoMenu.h"
#include "FileStream.h"

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


void MainMenu::Show(const bool _toAdd)
{
	Super::Show(_toAdd);

	DisplayLogo();

	function<void(const u_int&)> _callback = [&](const u_int& _index) { menus[_index]->Show(); };
	OpenMenu(menus, "JSP frr", _callback, false);
}

void MainMenu::DisplayLogo()
{
	FileStream::DisplayFile("Assets/Logo/Logo.txt", Gradient({ 222, 22, 35 }, { 24, 65, 230 }));
}

void MainMenu::Hide()
{
	system("cls");
}