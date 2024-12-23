#pragma once
#include "Menu.h"
#include "Save.h"

class StartMenu : public Menu
{
	vector<Save> allSaves;

public:
	StartMenu();

private:
	void LaunchGame(const string& _path);

public:
	virtual void Show(const bool _toAdd) override;
};