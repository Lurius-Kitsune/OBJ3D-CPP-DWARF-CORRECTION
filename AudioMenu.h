#pragma once
#include "Menu.h"

class AudioMenu : public Menu
{
public:
	virtual void Show(const bool _toAdd) override;
	virtual void Hide() override;
};