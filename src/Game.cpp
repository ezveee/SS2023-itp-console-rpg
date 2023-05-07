#include "Game.h"
#include "MoveMode.h"

void Game::run()
{
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
