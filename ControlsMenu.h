#pragma once
#include "Menu.h"
#include "GameInput.h"

class ControlsMenu : public Menu
{
	GameInput gameInputs;
public:
	ControlsMenu();

public:
	virtual void Show(const bool _toAdd) override;

	//void ChangeKey(pair<char, InputActionType> _inputToChange);
};