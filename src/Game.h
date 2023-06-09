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
	std::map<std::wstring, std::wstring> getDialogues();

	//Player player;

	Player* player;
	Team* playerTeam;
	
	GameMode* currentGameMode;
	GameMode* nextGameMode;

	std::map<std::wstring, std::wstring> dialogueMap;
};

