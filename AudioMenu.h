#pragma once
#include "Menu.h"

class AudioMenu : public Menu
{
public:
	virtual void Show() override;
	virtual void Hide() override;
};