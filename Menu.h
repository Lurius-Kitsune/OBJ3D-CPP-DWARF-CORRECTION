#pragma once
#include "CoreMinimal.h"

class Menu
{
	string title;
	Menu* owner;

public: 
	INLINE string GetTitle() const
	{
		return title;
	}
public:
	Menu(const string& _title);
public:
	virtual void Show() {};
	virtual void Hide() {};
};

