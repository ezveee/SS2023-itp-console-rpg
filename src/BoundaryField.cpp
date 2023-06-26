#include "BoundaryField.h"
#include "Game.h"
#include "defines.h"
#include <conio.h>

BoundaryField::BoundaryField(std::wstring& parameters)
{
	Game* game = Game::getInstance();
	size_t pos = parameters.find(';');
	boundaryName = parameters.substr(0, pos);
	auto iterator = game->boundaries.find(boundaryName);
	if (iterator == game->boundaries.end())
	{
		throw std::invalid_argument("Unknown boundary name key.");
	}
	enterable = iterator->second;
}
BoundaryField::~BoundaryField() = default;

void BoundaryField::onEnter(Game* game)
{
	// nothing to do
}

void BoundaryField::onInteract(Game* game)
{
	//nothing to do
}

bool BoundaryField::isEnterable()
{
	if (!this->enterable)
	{
		Game* game = game->getInstance();
		game->getUIManager()->showDialog(L"you are unable to pass by here for now, try talking to people to find out what you need to do in order to progress", true);
		_getch();
	}
	return this->enterable;
}

bool BoundaryField::isInteractable()
{
	return false;
}
