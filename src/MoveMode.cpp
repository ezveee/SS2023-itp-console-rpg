#include "MoveMode.h"
#include "MoveInput.h"
#include "Screen.h"
#include "Game.h"
#include "Command.h"
#include "WorldField.h"
#include <iostream>

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

	Position newPosition = game->player->calculateNewPosition(command);

	if (game->player->getInteractionRequested())
	{
		interact(currentScreen, game);
		game->player->setInteractionRequested();
	}

	if (currentScreen->getWorldField(newPosition.x, newPosition.y)->isEnterable())
	{
		game->player->setPosition(newPosition.x, newPosition.y);

		++moveCounter;
		
		currentScreen->getWorldField(newPosition.x, newPosition.y)->onEnter(game);

		if (nextScreen != nullptr)
		{
			delete currentScreen;
			currentScreen = nextScreen;
			nextScreen = nullptr;
		}
	}

	if (moveCounter >= stepsUntilEncounter)
	{
		moveCounter = 0;
		game->getUIManager()->showDialog(L"Enemy encountered!", true);
		game->nextGameMode = new FightMode();
	}
}

void MoveMode::interact(Screen* currentScreen, Game* game)
{
	Position currentPosition = game->player.getPosition();
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
