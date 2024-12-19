#include "Game.h"
#include "Dwarf.h"
#include "ControlsMenu.h" // TODO REMOVE
#include "MainMenu.h"

Game::Game()
{
	level = nullptr;
	/*cursor = new Cursor({ 109, 200 });*/
	//entities = 
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
    const int _code = _getch();
    if (_code == 27) // echap
    {
      /*  if (!isMenuOpen)
        {
            return true;
        }
        level->HideTileInfo();
        isMenuOpen = false;*/
    }
    if (_code == 13) // enter
    {
       /* level->ShowTileInfo();
        isMenuOpen = true;*/
    }
    else if (_code == 9) // tab
    {
        //system("cls");
        //displayAll = !displayAll; // toggle
    }
    else if (_code == 72) // haut
    {
        Cursor::GetInstance().Move(level, Coords(-1, 0));
    }
    else if (_code == 75) // gauche
    {
       Cursor::GetInstance().Move(level, Coords(0, -1));
    }
    else if (_code == 77) // droite
    {
        Cursor::GetInstance().Move(level, Coords(0, 1));
    }
    else if (_code == 80) // bas
    {
        Cursor::GetInstance().Move(level, Coords(1, 0));
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
	level->Display();
}

Level* Game::SelectLevel(const string& _path)
{
	level = new Level(_path, {109, 100});
    return level;
}

void Game::Start(Level* _level)
{
	level = _level;
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