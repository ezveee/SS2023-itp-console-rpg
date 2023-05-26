#include "BlockField.h"

BlockField::BlockField() = default;
BlockField::~BlockField() = default;

void BlockField::onEnter(Game* game)
{
	// nothing to do
}

void BlockField::onInteract(Game* game)
{

}

bool BlockField::isEnterable()
{
	return false;
}

bool BlockField::isInteractable()
{
	return false;
}
