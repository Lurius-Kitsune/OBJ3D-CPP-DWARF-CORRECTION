#pragma once
#include "Macro.h"
#include "Menu.h"
#include "Color.h"
#include "Cursor.h"
#include "Level.h"
#include "ControlsMenu.h"

class VideoMenu : public Menu
{
	Level* level;
	GameInput* gameInput;

public:

	VideoMenu(GameInput* _gameInput, Level* _level);

public:
	virtual void Show() override;
	virtual void Hide() override;

private:

	void DisplayMenu(int _selectedIndex, int& _brightness, int& _contrast);

	void DisplayProgressBar(const string& _label, int& _value, int _maxLength);

	void AdjustValue(int& _value, int _delta);

	int Clamp(int _value, int _min, int _max);
protected:
	virtual void Interact() override;
};