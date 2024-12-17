#include "Game.h"
#include "Dwarf.h"

Game::Game()
{
	level = nullptr;
	displayAll = false;
	cursor = new Cursor({ 35, 35 });
	isMenuOpen = false;
}

Game::~Game()
{
	delete cursor;

	for (Entity* _entity : entities)
	{
		delete _entity;
	}
}


bool Game::PollEvents()
{
	if (_kbhit())
	{
		const int _code = _getch();
		if (_code == 27) // echap
		{
			if (!isMenuOpen)
			{
				return true;
			}

			level->HideTileInfo();
			isMenuOpen = false;
		}
		if (_code == 13) // enter
		{
			level->ShowTileInfo();
			isMenuOpen = true;
		}
		else if (_code == 9) // tab
		{
			system("cls");
			displayAll = !displayAll; // toggle
		}

		else if (_code == 72) // haut
		{
			cursor->Move(level, Coords(0, -1));
		}
		else if (_code == 75) // gauche
		{
			cursor->Move(level, Coords(-1, 0));
		}
		else if (_code == 77) // droite
		{
			cursor->Move(level, Coords(1, 0));
		}
		else if (_code == 80) // bas
		{
			cursor->Move(level, Coords(0, 1));
		}
	}

	return false;
}

void Game::UpdateEntities()
{
	for (Entity* _entity : entities)
	{
		_entity->Update();
	}
}

void Game::Display() const
{
	if (displayAll)
	{
		level->DisplayFullMap();
	}
	else
	{
		const Coords& _center = Coords(35, 35);
		level->DisplayView(_center);
	}
}


void Game::SelectLevel(const string& _path)
{
	level = new Level(_path, cursor);
}

void Game::Start()
{
	SLEEP(seconds, 3);
	entities.push_back(new Dwarf());
	Update();
}

void Game::Update()
{
	bool _wantToExit = false;
	while (!_wantToExit)
	{
		if (PollEvents()) break;
		UpdateEntities();
		Display();
	}

	Stop();
}

void Game::Pause()
{
}

void Game::Stop()
{
	delete level;
}