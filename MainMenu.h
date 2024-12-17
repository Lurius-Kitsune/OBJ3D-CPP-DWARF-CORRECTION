#pragma once
#include "Menu.h"
#include "StartMenu.h"
#include "OptionsMenu.h"

class MainMenu: public Menu
{
	vector<Menu*> menus;

public:
	MainMenu();
	~MainMenu();

public:
	virtual void Show() override;
	virtual void Hide() override;

};

