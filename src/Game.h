#pragma once

#include "Player.h"
#include <map>
#include <string>

class GameMode;

class Game
{
public:
	Game() = default;
	virtual ~Game() = default;
	void run();
	std::map<std::string, std::string> getDialogues();

	Player player;
	
	GameMode* currentGameMode;
	GameMode* nextGameMode;

	std::map<std::string, std::string> dialogueMap;
};

