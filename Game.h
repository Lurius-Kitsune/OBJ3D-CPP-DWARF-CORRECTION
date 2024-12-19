#pragma once
#include "CoreMinimal.h"
#include "Level.h"
#include "Cursor.h"
#include "GameInput.h"
#include "VideoMenu.h"

#pragma region ToDelete
#include "Color.h"
#include "Random.h"
#include "Emoji.h"
#pragma endregion

class Game
{
	Level* level;
	Cursor* cursor;
	GameInput gameInput;
	vector<Entity*> entities;
	
	bool isMenuOpen;

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

	void ToDelete(const string& _fileName = "ChouetteMouillee.txt");
};