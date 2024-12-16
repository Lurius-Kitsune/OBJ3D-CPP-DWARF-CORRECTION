#include "Game.h"
#include "Macro.h"

Game::Game()
{
	level = nullptr;
	cursor = new Cursor({10, 10});
}

Game::~Game()
{
	delete level;
	delete cursor;
}

void Game::SelectLevel()
{
	const string& _path = "DefaultLevel.txt";
	level = new Level(_path, cursor);
}

void Game::Start()
{
	SLEEP(seconds, 3);
	Update();
}

void Game::Update()
{
	bool _wantToExit = false;
	while (!_wantToExit)
	{
		if (_kbhit())
		{
			if (_getch() == 27)
			{
				_wantToExit = true;
				continue;
			}
			displayAll = !displayAll;
			CLEAR_SCREEN;
		}
		cursor->SetCursorPosition(0, 0);
		const Size& _center = level->GetFullSize() / 2;
		if (displayAll)
		{
			level->DisplayFullMap();
		}
		else
		{
			level->DisplayView(Coords(_center));
		}
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
