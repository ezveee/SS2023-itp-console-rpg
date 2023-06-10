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
	Game();
	virtual ~Game();
	void run();

	static Game* getInstance();
	UIManager* getUIManager() const { return this->uiManager; };

	std::map<std::wstring, std::wstring> getDialogues();
	void generateMaps();
	std::vector<std::wstring> getSaveFile();
	void loadSaveFile(Player* player, std::vector<std::wstring> lines);

	Player* player;
	Team* playerTeam;
	
	GameMode* currentGameMode;
	GameMode* nextGameMode;

	std::map<std::wstring, std::wstring> dialogueMap;
	std::map<std::wstring, bool> boundaryMap;
	std::map<std::wstring, std::map<std::wstring, bool>::iterator> storyNpcs;

	std::wstring currentScreenName = L"Village_2";

private:
	static Game* instance;
	UIManager* uiManager;
};

