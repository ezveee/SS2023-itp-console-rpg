#include "Game.h"
#include "MoveMode.h"
#include <fstream>
#include <vector>
#include <iostream>

void Game::run()
{
	loadSaveFile(&(this->player), getSaveFile());
	this->generateMaps();
	currentGameMode = new MoveMode(this);
	nextGameMode = nullptr;

	while (!player.getIsExitRequested())
	{
		currentGameMode->handle(this);

		if (nextGameMode != nullptr)
		{
			delete currentGameMode;
			currentGameMode = nextGameMode;
			nextGameMode = nullptr;
		}
	}

	delete currentGameMode;
}

void Game::generateMaps()
{
	this->dialogueMap =
	{
		{L"Castle_npc", L"hello i am the castle npc\ntalk to me again to unlock\nthe barrier to the next area!"},
		{L"Village_npc_1", L"i will give you a tutorial\nfor now i am just here to test\nthe dialogue function" },
	};

	this->storyNpcs =
	{
		{L"Castle_npc", this->boundaryMap.find(L"City_1_Gate")},
	};
}

std::vector<std::wstring> Game::getSaveFile()
{
	std::wifstream file(L"./Savefiles/save.txt", std::ios::binary);

	if (!file.is_open())
	{
		throw std::runtime_error("Could not open file ");
	}

	std::vector<std::wstring> lines;
	std::wstring line;

	while (std::getline(file, line))
	{
		lines.push_back(line.substr(0, line.length() - 1));
	}
	file.close();

	return lines;
}

void Game::loadSaveFile(Player* player, std::vector<std::wstring> lines)
{
	//add loading for playerstats

	for (int lineNr = 6; lineNr < lines.size(); ++lineNr)
	{
		size_t pos = lines[lineNr].find(';');
		this->boundaryMap.insert(std::pair<std::wstring, bool>(lines[lineNr].substr(0, pos), stoi(lines[lineNr].substr(pos + 1))));
	}
}
