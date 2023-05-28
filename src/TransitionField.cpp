#include <stdexcept>

#include "TransitionField.h"
#include "Game.h"
#include "GameMode.h"
#include "MoveMode.h"
#include "Screen.h"

TransitionField::TransitionField(std::wstring& parameters)
{
	std::wstring coordinates;
	size_t pos = parameters.find(';');
	if (pos != std::wstring::npos)
	{
		mapName = parameters.substr(0, pos);
		coordinates = parameters.substr(pos + 1);
	}
	else
	{
		mapName = parameters;
		coordinates = L"X:-1;Y:-1";
	}

	pos = coordinates.find(';');
	if (pos != std::wstring::npos)
	{
		xPos = getCoordinate(coordinates.substr(0, pos));
		yPos = getCoordinate(coordinates.substr(pos + 1));
	}
	else
	{
		xPos = getCoordinate('X', coordinates);
		yPos = getCoordinate('Y', coordinates);
	}
}

TransitionField::~TransitionField() = default;

void TransitionField::onEnter(Game* game)
{
	((MoveMode*)game->currentGameMode)->nextScreen = new Screen(mapName);
	if (xPos == -1)
	{
		xPos = game->player.getPosition().x;
	}
	if (yPos == -1)
	{
		yPos = game->player.getPosition().y;
	}
	game->player.setPosition(xPos, yPos);
}

bool TransitionField::isEnterable()
{
	return true;
}

int TransitionField::getCoordinate(std::wstring text)
{
	return std::stoi(text.substr(2));
}

int TransitionField::getCoordinate(char axis, std::wstring text)
{
	if (text[0] != axis)
	{
		return -1;
	}
	return getCoordinate(text);
}
