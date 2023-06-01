#include "MoveMode.h"
#include "MoveInput.h"
#include "Screen.h"
#include "Game.h"
#include "Command.h"
#include "WorldField.h"

MoveMode::MoveMode()
{
	currentUserInput = new MoveInput();
	currentScreen = new Screen(L"City_1_3");
	nextScreen = nullptr;
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

	Position newPosition = game->player.calculateNewPosition(command);
	if (currentScreen->getWorldField(newPosition.x, newPosition.y)->isEnterable())
	{
		game->player.setPosition(newPosition.x, newPosition.y);
		currentScreen->getWorldField(newPosition.x, newPosition.y)->onEnter(game);

		if (nextScreen != nullptr)
		{
			delete currentScreen;
			currentScreen = nextScreen;
			nextScreen = nullptr;
		}
	}
}
