#include "Game.h"
#include "Macro.h"

Game::Game()
{
	level = nullptr;
	cursor = new Cursor({35, 35});
}

Game::~Game()
{
	delete level;
	delete cursor;
}

bool Game::PoleEvent()
{
	if (_kbhit())
	{
		const int _code = _getch();
		cout << _code << endl;
		if (_code == 27)
		{
			if (!isMenuOpen)
			{
				return true;
			}
		}
		if (_code == 13)
		{
			level->ShowTileInfo();
			isMenuOpen = true;
		}
		else if (_code == 9)
		{
			displayAll = !displayAll;
			CLEAR_SCREEN;
		}
		else if (_code == 72)
		{
			level->ResetItemAtLocation(cursor->GetCoords());
			cursor->Move(level ,Coords(-1, 0));
			level->SetItemAtLocation(cursor->GetAppearance(), cursor->GetCoords());
		}
		else if (_code == 75)
		{
			cursor->Move(level, Coords(0, -1));
		}
		else if (_code == 77)
		{
			cursor->Move(level, Coords(0, 1));
		}
		else if (_code == 80)
		{
			cursor->Move(level ,Coords(1, 0));
		}
	}
	
	return false;
}

void Game::Display()
{
	cursor->SetCursorPosition(0, 0, false);
	if (displayAll)
	{	
		level->DisplayFullMap();
	}
	else
	{
		level->DisplayView(cursor->GetCoords());
	}
}

void Game::SelectLevel(const string& _path)
{
	const string& _path = "MainLevel.txt";
	level = new Level(_path, cursor);
}

void Game::Start()
{
	//SLEEP(seconds, 3);
	Update();
}

void Game::Update()
{
	bool _wantToExit = false;
	while (!_wantToExit)
	{
		_wantToExit = PoleEvent();
		Display();
	}
	level->Save();
	Stop();
}

void Game::Pause()
{
}

void Game::Stop()
{
	delete level;
	level = nullptr;
	delete cursor;
	cursor = nullptr;
}
