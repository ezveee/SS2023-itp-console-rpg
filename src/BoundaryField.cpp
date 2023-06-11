#include "BoundaryField.h"
#include "Game.h"
#include <conio.h>

BoundaryField::BoundaryField(std::wstring& parameters)
{
	Game* game = Game::getInstance();
	size_t pos = parameters.find(';');
	boundaryName = parameters.substr(0, pos);
	auto iterator = game->boundaryMap.find(boundaryName);
	if (iterator == game->boundaryMap.end())
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
		std::wcout << L"you are unable to pass by here for now,\ntry talking to people to find out what\nyou need to do in order to progress\n";
		_getch();
	}
	return this->enterable;
}

bool BoundaryField::isInteractable()
{
	return false;
}
