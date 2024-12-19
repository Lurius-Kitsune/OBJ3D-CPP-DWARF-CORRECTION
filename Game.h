#pragma once
#include "CoreMinimal.h"
#include "Level.h"
#include "Cursor.h"
#include "Entity.h"
#include "Menu.h"

class Game
{
	Level* level;
	Cursor* cursor;
	vector<Entity*> entities;

public:
	Game();
	~Game();

private:
	bool PollEvents();
	void UpdateEntities();
	void Display() const;

public:
	void SelectLevel(const string& _path);
	void Start();
	void Update();
	void Pause();
	void Stop();
};