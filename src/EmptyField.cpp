#include "EmptyField.h"

EmptyField::EmptyField() = default;
EmptyField::~EmptyField() = default;

void EmptyField::onEnter(Game* game)
{

}

bool EmptyField::isEnterable()
{
	return true;
}
