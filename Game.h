#pragma once
#include "CoreMinimal.h"
#include "Level.h"
#include "Cursor.h"

class Game
{
	Level* level;
	Cursor* cursor;
	bool displayAll = false;
public:
	Game();
	~Game();

public:
	bool PoleEvent();
	void Display();
	void SelectLevel();
	void Start();
	void Update();
	void Pause();
	void Stop();
};

