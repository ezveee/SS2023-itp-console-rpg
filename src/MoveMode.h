#pragma once

#include "GameMode.h"

class Game;
class Screen;

class MoveMode : public GameMode
{
public:
	MoveMode();
	virtual ~MoveMode();

	void handle(Game* game) override;

	Screen* currentScreen;
	Screen* nextScreen;
};

