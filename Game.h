#pragma once
#include "CoreMinimal.h"
#include "Level.h"
#include "Cursor.h"
#include "Entity.h"
#include "Singleton.h"

class Game : public Singleton<Game>
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
	Level* SelectLevel(const string& _path);
	void Start(Level* _level);
	void Update();
	void Pause();
	void Stop();
};