#pragma once
#include "Menu.h"

class Game;

struct Save
{
	string title;
	string path;

	Save()
	{
		title = "Empty";
		path = "";
	}
	Save(const string& _title, const string& _path)
	{
		title = _title;
		path = _path;
	}
};

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