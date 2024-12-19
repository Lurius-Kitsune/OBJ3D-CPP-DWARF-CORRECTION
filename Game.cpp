#include "Game.h"
#include "Entity.h"

Game::Game()
{
	level = nullptr;
	displayAll = false;
	gameInput = GameInput();
	cursor = new Cursor({ 109, 200 });
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
		InputActionType _inputAction = gameInput.GetInputActionType(_getch());
		if (_inputAction == IAT_PAUSE) // echap
		{
			if (!isMenuOpen)
			{
				isMenuOpen = true;
			}

			level->HideTileInfo();
			//isMenuOpen = false;
		}
		if (_inputAction == IAT_INTERACT) // enter
		{
			level->ShowTileInfo();
			isMenuOpen = true;
		}
		else if (_inputAction == IAT_TAB) // tab
		{
			system("cls");
			displayAll = !displayAll; // toggle
		}

		else if (_inputAction == IAT_UP) // haut
		{
			if (isMenuOpen)
			{
				//currentMenu->AddOnCurrentIndex(-1);
			}
			else
			{
				cursor->Move(level, Coords(-1, 0));
			}
		}
		else if (_inputAction == IAT_LEFT) // gauche
		{
			cursor->Move(level, Coords(0, -1));
		}
		else if (_inputAction == IAT_RIGHT) // droite
		{
			cursor->Move(level, Coords(0, 1));
		}
		else if (_inputAction == IAT_DOWN) // bas
		{
			if (isMenuOpen)
			{
				//currentMenu->AddOnCurrentIndex(1);
			}
			else
			{
				cursor->Move(level, Coords(1, 0));
			}
		}
		else if (_inputAction == IAT_VALIDATE) // entr�
		{

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
	cursor->SetCursorPosition(0, 0);
	displayAll ? level->DisplayFullMap() : level->DisplayView(cursor->GetLocation());
}

void Game::SelectLevel(const string& _path)
{
	level = new Level(_path, cursor);
}

void Game::Start()
{
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