#pragma once

#include "Player.h"

class GameMode;

class Game
{
public:
	Game() = default;
	virtual ~Game() = default;
	void run();

	Player player;
	
	GameMode* currentGameMode;
	GameMode* nextGameMode;
};

