#pragma once
#include "CoreMinimal.h"

class Menu
{
	string title;

protected:
	Menu* owner;
	int currentIndex;
	int maxChoice;

public:
	INLINE string GetTitle() const
	{
		return title;
	}

	void AddOnCurrentIndex(const int _value)
	{
		if (currentIndex + _value >= maxChoice)
		{
			currentIndex = 0;
		}
		else if (currentIndex + _value < 0)
		{
			currentIndex = maxChoice - 1;
		}
		else
		{
			currentIndex += _value;
		}
	}


public:
	Menu(const string& _title, const int _maxChoice);
	Menu(const string& _title, Menu* _owner, const int _maxChoice);

public:

	virtual void Show() {};
	virtual void Hide() {};
	virtual void Interact() {};
};