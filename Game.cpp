#include "Game.h"
#include "VideoMenu.h"
#include "Dwarf.h"
#include "MovementComponent.h"

Game::Game()
{
	level = nullptr;
	entities = vector<Entity*>();
}

Game::~Game()
{
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
        }
        if (_code == 13) // enter
        {
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
	}

	return false;
}

void Game::InitDwarfs()
{
    const Coords& _cursorPos = Cursor::GetInstance().GetLocation();
    Coords _startLocation;

    Dwarf* _dwarf1 = new Dwarf(DWARF);
    _startLocation = _cursorPos + Coords(-2, 0);
    _dwarf1->SetLocation(_startLocation);
    _dwarf1->GetComponent<MovementComponent>()->SetTargetLocation(_startLocation + Coords(0, 27));
    entities.push_back(_dwarf1);

    Dwarf* _dwarf2 = new Dwarf(DWARF);
    _startLocation = _cursorPos + Coords(2, 0);
    _dwarf2->SetLocation(_startLocation);
    if (MovementComponent* _movement = _dwarf2->GetComponent<MovementComponent>())
    {
        _movement->SetSpeed(2);
        _movement->SetTargetLocation(_startLocation + Coords(0, 27));
    }
   
    entities.push_back(_dwarf2);
}

void Game::Start(Level* _level)
{
	level = _level;

    InitDwarfs();
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
        SLEEP(milliseconds, 50);
	}

	Stop();
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

void Game::Pause()
{

}

void Game::Stop()
{
	delete level;
}