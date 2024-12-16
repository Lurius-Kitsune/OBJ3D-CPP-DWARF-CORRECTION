#include "Game.h"

Game::Game()
{
	level = nullptr;
	cursor = new Cursor();
}

Game::~Game()
{
	delete level;
	delete cursor;
}

void Game::SelectLevel()
{
	const string& _path = "DefaultLevel.txt";
	level = new Level(_path);
}

void Game::StartGame()
{
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
		}

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
