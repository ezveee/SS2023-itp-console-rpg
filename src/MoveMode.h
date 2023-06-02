#pragma once

#include "GameMode.h"
#include "position.h"

class Game;
class Screen;

class MoveMode : public GameMode
{
public:
	MoveMode();
	virtual ~MoveMode();

	void handle(Game* game) override;
	void interact(Screen* currentScreen, Game* game);

	Screen* currentScreen;
	Screen* nextScreen;
};

