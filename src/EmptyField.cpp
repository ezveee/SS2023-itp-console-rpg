#include "EmptyField.h"

EmptyField::EmptyField() = default;
EmptyField::~EmptyField() = default;

void EmptyField::onEnter(Game* game)
{

}

void EmptyField::onInteract(Game* game)
{

}

bool EmptyField::isEnterable()
{
	return true;
}

bool EmptyField::isInteractable()
{
	return false;
}
