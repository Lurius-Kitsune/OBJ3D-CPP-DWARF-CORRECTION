#pragma once
#include "Singleton.h"
#include "Level.h"
#include "Entity.h"

class Game : public Singleton<Game>
{
	Level* level;
	vector<Entity*> entities;

public:
	INLINE Level* GetLevel() const
	{
		return level;
	}

public:
	Game();
	~Game();

private:
	bool PollEvents();
	void InitDwarfs();
	void UpdateEntities();
	void Display() const;

public:
	void Start(Level* _level);
	void Update();
	void Pause();
	void Stop();
};