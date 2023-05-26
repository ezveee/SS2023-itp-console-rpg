#include "NpcField.h"
#include <iostream>
#include <conio.h>

NpcField::NpcField(std::string& parameters)
{

}

NpcField::~NpcField() = default;

void NpcField::onEnter(Game* game)
{
	// nothing to do
}

void NpcField::onInteract(Game* game)
{
	std::cout << TEXTBOXBORDER_UPPER_LOWER << "\nHello, i am a npc :D\n\n" << TEXTBOXBORDER_UPPER_LOWER << "\n";
	_getch();
}

bool NpcField::isEnterable()
{
	return false;
}

bool NpcField::isInteractable()
{
	return true;
}
