#pragma once
#include "Menu.h"

class ControlsMenu : public Menu
{

public:
	ControlsMenu();

public:
	virtual void Show(const bool _toAdd) override;
};