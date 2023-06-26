#include "MoveMode.h"
#include "MoveInput.h"
#include "Screen.h"
#include "Game.h"
#include "Command.h"
#include "WorldField.h"
#include <iostream>
#include <conio.h>

MoveMode::MoveMode(Game* game)
{
	currentUserInput = new MoveInput();
	currentScreen = new Screen(game->currentScreenName);
	nextScreen = nullptr;

	stepsUntilEncounter = rand() % 9 + 8;
}

MoveMode::~MoveMode()
{
	delete currentScreen;
}

void MoveMode::handle(Game* game)
{
	system("CLS");
	currentScreen->display(game->player);
	Command command = currentUserInput->getUserInput();
	if (command == Command::OpenMenu)
		openMenu(game);

	Position newPosition = game->player->calculateNewPosition(command);

	if (game->player->getInteractionRequested())
	{
		interact(currentScreen, game);
		game->player->setInteractionRequested();
	}

	if (currentScreen->getWorldField(newPosition.x, newPosition.y)->isEnterable())
	{
		game->player->setPosition(newPosition.x, newPosition.y);

		if(!currentScreen->getIsSafe())
			++moveCounter;
		
		currentScreen->getWorldField(newPosition.x, newPosition.y)->onEnter(game);

		if (nextScreen != nullptr)
		{
			delete currentScreen;
			currentScreen = nextScreen;
			nextScreen = nullptr;
		}
	}
	if(!currentScreen->getIsSafe())
	{
		if (moveCounter >= stepsUntilEncounter)
		{
			moveCounter = 0;
			game->getUIManager()->showDialog(L"Enemy encountered!", true);
			game->nextGameMode = new FightMode();
		}
	}
}

void MoveMode::interact(Screen* currentScreen, Game* game)
{
	Position currentPosition = game->player->getPosition();
	for (auto field : {
		currentScreen->getWorldField(currentPosition.x - 1, currentPosition.y),
		currentScreen->getWorldField(currentPosition.x, currentPosition.y - 1),
		currentScreen->getWorldField(currentPosition.x + 1, currentPosition.y),
		currentScreen->getWorldField(currentPosition.x, currentPosition.y + 1)
		})
	{
		if (field->isInteractable())
		{
			field->onInteract(game);
		}
	}
}

void MoveMode::openMenu(Game* game)
{
	system("CLS");
	std::wstring currentMiniMap;
	size_t pos = game->currentScreenName.find('_');

	if (game->currentScreenName.substr(0, pos) == L"Village")
		currentMiniMap = THUMBNAIL_MAP_VILLAGE;
	if (game->currentScreenName.substr(0, pos) == L"Castle")
		currentMiniMap = THUMBNAIL_MAP_CITY_1;
	else{
		auto iterator = game->miniMaps.find(game->currentScreenName.substr(0, 6));
		if (iterator == game->miniMaps.end())
		{
			throw std::invalid_argument("Unknown map name key.");
		}
		currentMiniMap = iterator->second;
	}

	std::wcout << L"Your current Position:\n" << game->currentScreenName << "\n"
		<< "\nMinimap: " << currentMiniMap << L"________________________________________\n\n";
	std::wcout << game->player->getGold() << L"G\n" << "Weapon lvl: " << game->player->getWeaponLevel() << "\n\n";


	for (auto member : game->playerTeam->members){
		std::wcout << L"=" << member->getName() << L"=\n"
		<< L"Level " << member->getStats().level << " " << member->getRoleString() << "\n"
		<< L"HP: " << member->getStats().health << "/" << member->getStats().maxHealth << "\n"
		<< L"MP: " << member->getStats().mana << "/" << member->getStats().maxMana << "\n\n";
	}

	std::wcout << "\n";

	for (auto member : game->playerTeam->members){
		
	}
	std::wcout << "\n";
	for (auto member : game->playerTeam->members){
		
	}
	std::wcout << "\n";
	_getch();
}
