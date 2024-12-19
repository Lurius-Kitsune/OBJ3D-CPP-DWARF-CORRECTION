#pragma once
#include "Menu.h"
#include "GameInput.h"
#include "Level.h"
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