#include "Game.h"
#include "Player.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <time.h>


Game* Game::instance = nullptr;

Game* Game::getInstance()
{
	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;
}

Game::Game()
{
	uiManager = new UIManager();

	//add dialogue map
	this->dialogueMap = this->getDialogues();

	currentGameMode = new MoveMode(this);
	nextGameMode = nullptr;
}

Game::~Game()
{
	delete uiManager;
	delete currentGameMode;
}

void Game::run()
{
	srand(time(NULL));

	while (!player->getIsExitRequested())
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

std::map<std::wstring, std::wstring> Game::getDialogues()
{
	return
	{
		{L"Castle_npc", L"hello i am the castle npc\ni will give you directions\nto your next task!"},
		{L"Village_npc_1", L"i will give you a tutorial\nfor now i am just here to test\nthe dialogue function"},
	};
}
