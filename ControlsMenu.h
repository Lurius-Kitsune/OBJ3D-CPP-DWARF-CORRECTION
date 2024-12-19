#pragma once
#include "Menu.h"
#include "GameInput.h"

class ControlsMenu : public Menu
{
	GameInput* gameInputs;
public:
	ControlsMenu(GameInput* _gameInput);

public:
	virtual void Show() override;
	virtual void Hide() override;
	virtual void Interact() override;

	void ChangeKey(pair<char, InputActionType> _inputToChange);
};