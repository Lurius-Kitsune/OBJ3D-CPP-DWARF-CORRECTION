#pragma once
#include "Macro.h"
#include "Menu.h"
#include "Color.h"
#include "Cursor.h"
#include "Level.h"
#include "ControlsMenu.h"

class VideoMenu : public Menu
{
public:

	VideoMenu();

private:

	void DisplayMenu(int _selectedIndex, int& _brightness, int& _contrast);

	void DisplayProgressBar(const string& _label, int& _value, int _maxLength);

	void AdjustValue(u_int& _value, const u_int& _delta);

protected:
	virtual void Interact() override;

public:
	virtual void Show(const bool _toAdd) override;
};