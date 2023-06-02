#include "Game.h"
#include "MoveMode.h"
#include <fstream>
#include <vector>
#include <iostream>


void Game::run()
{
	//add dialogue map
	this->dialogueMap = this->getDialogues();
	currentGameMode = new MoveMode();
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

std::map<std::wstring, std::wstring> Game::getDialogues()
{
	return
	{
		{L"Castle_npc", L"hello i am the castle npc\ni will give you directions\nto your next task!"},
		{L"Village_npc_1", L"i will give you a tutorial\nfor now i am just here to test\nthe dialogue function"},
	};
}
