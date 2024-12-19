#pragma once
#include "Menu.h"

class OptionsMenu : public Menu
{
public:
	OptionsMenu();

public:
	virtual void Show() override;
	virtual void Hide() override;
};