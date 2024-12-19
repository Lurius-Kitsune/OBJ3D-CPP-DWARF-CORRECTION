#pragma once
#include "Menu.h"

class VideoMenu : public Menu
{
public:
	virtual void Show() override;
	virtual void Hide() override;
};