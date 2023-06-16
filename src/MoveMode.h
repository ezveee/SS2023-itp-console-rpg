#pragma once

#include "GameMode.h"
#include "position.h"

class Game;
class Screen;

class MoveMode : public GameMode
{
public:
	MoveMode(Game* game);
	virtual ~MoveMode();

	void handle(Game* game) override;
	void interact(Screen* currentScreen, Game* game);
	void openMenu(Game* game);

	Screen* currentScreen;
	Screen* nextScreen;

private:
	int moveCounter = 0;
	int stepsUntilEncounter;
};

