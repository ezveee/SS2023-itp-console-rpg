#pragma once

#include <string>
#include "Game.h"

class Game;

class WorldField
{
public:
	WorldField();
	virtual ~WorldField();

	virtual void onEnter(Game* game) = 0;
	virtual void onInteract(Game* game) = 0;
	virtual bool isEnterable() = 0;
	virtual bool isInteractable() = 0;

	char getSign() const;
	void setSign(char sign);

	std::string getInfo() const;
	void setInfo(std::string info);

private:
	char sign;
	std::string info;
};

