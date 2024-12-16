#pragma once
#include "CoreMinimal.h"
#include "Level.h"
#include "Cursor.h"

class Game
{
	Level* level;
	Cursor* cursor;
	bool displayAll = true;
public:
	Game();
	~Game();

public:
	void SelectLevel();
	void Start();
	void Update();
	void Pause();
	void Stop();
};

