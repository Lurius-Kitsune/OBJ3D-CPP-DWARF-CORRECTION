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

public:

	VideoMenu();

private:

	void DisplayMenu(u_int _selectedIndex, u_int& _brightness, u_int& _contrast);
	void DisplayProgressBar(const string& _label, u_int& _value, int _maxLength);
	void AdjustValue(u_int& _value, const u_int& _delta);

protected:
	//virtual void Interact() override;

public:
	virtual void Show(const bool _toAdd) override;
};