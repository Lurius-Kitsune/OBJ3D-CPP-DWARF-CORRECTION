#pragma once
#include "Menu.h"
#include "GameInput.h"
#include "Level.h"

class MainMenu : public Menu
{
	vector<Menu*> menus;

public:
	MainMenu();
	~MainMenu();

public:
	virtual void Show(const bool _toAdd = true) override;
	void DisplayLogo();
	virtual void Hide() override;
};