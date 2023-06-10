#pragma once

#include "Player.h"
#include <map>
#include <string>
#include <vector>

class GameMode;

class Game
{
public:
	Game() = default;
	virtual ~Game() = default;
	void run();
	void generateMaps();
	std::vector<std::wstring> getSaveFile();
	void loadSaveFile(Player* player, std::vector<std::wstring> lines);

	Player player;
	
	GameMode* currentGameMode;
	GameMode* nextGameMode;

	std::map<std::wstring, std::wstring> dialogueMap;
	std::map<std::wstring, bool> boundaryMap;
	std::map<std::wstring, std::map<std::wstring, bool>::iterator> storyNpcs;
};

