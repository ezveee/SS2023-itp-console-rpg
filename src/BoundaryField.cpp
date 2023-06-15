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
	bool test = iterator->second;
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
		std::wcout << TEXTBOXBORDER_UPPER_LOWER << L"\nyou are unable to pass by here for now,\ntry talking to people to find out what\nyou need to do in order to progress\n"
		<< TEXTBOXBORDER_UPPER_LOWER;
		_getch();
	}
	return this->enterable;
}

bool BoundaryField::isInteractable()
{
	return false;
}
