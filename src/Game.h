#pragma once

#include <map>
#include <string>
#include "Player.h"
#include "UIManager.h"

#include "FightMode.h"
#include "MoveMode.h"

class GameMode;

class Game
{
public:
	Game();
	virtual ~Game();
	void run();

	static Game* getInstance();
	UIManager* getUIManager() const { return this->uiManager; };

	std::map<std::wstring, std::wstring> getDialogues();

	Player* player;
	Team* playerTeam;
	
	GameMode* currentGameMode;
	GameMode* nextGameMode;

	std::map<std::wstring, std::wstring> dialogueMap;

	std::wstring currentScreenName = L"Village_2";

private:
	static Game* instance;
	UIManager* uiManager;
};

