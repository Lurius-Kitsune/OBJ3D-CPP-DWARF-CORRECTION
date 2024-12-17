#pragma once
#include "Menu.h"

class StartMenu : public Menu
{
public: 
	StartMenu();
public:
	virtual void Show() override;
	virtual void Hide() override;
};

