#pragma once
#include "Menu.h"
#include "GameInput.h"
#include "Level.h"

class MainMenu : public Menu
{
	vector<Menu*> menus;

public:
	MainMenu(GameInput* _gameInput, Level* _level);
	~MainMenu();

public:
	virtual void Show() override;
	virtual void Hide() override;
};