#pragma once
#include "Menu.h"
#include "ControlsMenu.h"
#include "VideoMenu.h"

class Level;

class OptionsMenu : public Menu
{
	vector<Menu*> menus;

public:
	OptionsMenu();
	~OptionsMenu();

public:
	virtual void Show(const bool _toAdd = true) override;
	virtual void Interact() override;
};