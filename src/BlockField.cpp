#include "BlockField.h"

BlockField::BlockField() = default;
BlockField::~BlockField() = default;

void BlockField::onEnter()
{
	// nothing to do
}

bool BlockField::isEnterable()
{
	return false;
}
