#include "Menu.h"

Menu::Menu(const string& _title, const int _maxChoice)
{
	title = _title;
	owner = nullptr;
	currentIndex = 0;
	maxChoice = _maxChoice;
}

Menu::Menu(const string& _title, Menu* _owner, const int _maxChoice)
{
	title = _title;
	owner = _owner;
	currentIndex = 0;
	maxChoice = _maxChoice;
}
