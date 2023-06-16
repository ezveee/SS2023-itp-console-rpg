#pragma once

#include <map>
#include <string>
#include "Player.h"
#include "UIManager.h"
#include <vector>

#include "FightMode.h"
#include "MoveMode.h"

class GameMode;

class Game
{
public:
	virtual ~Game();
	void run();

	static Game* getInstance();
	UIManager* getUIManager() const { return this->uiManager; };

	void generateMaps();
	std::vector<std::wstring> getSaveFile();
	Player* loadSaveFile(std::vector<std::wstring> lines);

	Player* player;
	Team* playerTeam;
	
	GameMode* currentGameMode;
	GameMode* nextGameMode;

	std::map<std::wstring, std::wstring> dialogues;
	std::map<std::wstring, bool> boundaries;
	std::map<std::wstring, std::map<std::wstring, bool>::iterator> storyNpcs;
	std::map<std::wstring, std::wstring> miniMaps;
	std::map<std::wstring, std::wstring> respawn;

	std::wstring currentScreenName = L"City_1_1";

private:
	static Game* instance;
	Game();
	UIManager* uiManager;
};

