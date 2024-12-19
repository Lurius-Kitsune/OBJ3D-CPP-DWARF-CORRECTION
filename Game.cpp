#include "Game.h"
#include "Dwarf.h"
#include "ControlsMenu.h" // TODO REMOVE
#include "MainMenu.h"

Game::Game()
{
	level = nullptr;
	cursor = new Cursor({ 109, 200 });
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
	if (_kbhit())
	{

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

void Game::SelectLevel(const string& _path)
{
	level = new Level(_path);
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