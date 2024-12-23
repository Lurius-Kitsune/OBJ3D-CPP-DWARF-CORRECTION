#include "Menu.h"

Menu::Menu(const string& _title)
{
	title = _title;
}

void Menu::Show(const bool _toAdd)
{
	CLEAR;

	if (_toAdd)
	{
		queue.push(this);
	}

	// Override to display
}

void Menu::Hide()
{
	queue.pop();

	if (Menu* _previous = queue.back())
	{
		_previous->Show(false);
	}
}

void Menu::Close()
{
	while (Menu* _previous = queue.back())
	{
		queue.pop();
	}
}

ostream& operator << (ostream& _stream, Menu* _other)
{
	return _stream << _other->GetTitle();
}