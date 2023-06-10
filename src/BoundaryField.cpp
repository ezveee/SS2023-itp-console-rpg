#include "BoundaryField.h"

BoundaryField::BoundaryField(std::wstring& parameters, Game* game)
{
	size_t pos = parameters.find(';');
	boundaryName = parameters.substr(0, pos);
	auto iterator = game->boundaryMap.find(boundaryName);
	if (iterator == game->boundaryMap.end())
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
	return this->enterable;
}

bool BoundaryField::isInteractable()
{
	return false;
}
