#pragma once
#include "Menu.h"

class SelectGameMenu : public Menu
{
public:
	virtual void Show() override;
	virtual void Hide() override;
};