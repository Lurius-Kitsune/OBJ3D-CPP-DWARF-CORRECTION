#pragma once
#include "Menu.h"
#include "ControlsMenu.h"
#include "VideoMenu.h"

class Level;

class OptionsMenu : public Menu
{
	vector<Menu*> menus;

public:
	OptionsMenu(GameInput* _gameInput, Level* _level);
	OptionsMenu(Menu* _parent, GameInput* _gameInput, Level* _level);
	~OptionsMenu();

public:
	virtual void Show() override;
	virtual void Hide() override;
	virtual void Interact() override;
};