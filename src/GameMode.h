#pragma once

class Game;
class UserInput;

class GameMode
{
public:
	GameMode() = default;
	virtual ~GameMode() = default;

	UserInput* currentUserInput;

	virtual void handle(Game* game) = 0;
};

