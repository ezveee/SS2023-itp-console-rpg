#include "BlockField.h"

BlockField::BlockField() = default;
BlockField::~BlockField() = default;

void BlockField::onEnter(Game* game)
{
	// nothing to do
}

bool BlockField::isEnterable()
{
	return false;
}
