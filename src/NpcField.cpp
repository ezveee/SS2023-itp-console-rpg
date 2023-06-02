#include "NpcField.h"
#include <iostream>
#include <conio.h>

NpcField::NpcField(std::string& parameters)
{
	size_t pos = parameters.find(';');
	npcName = parameters.substr(0, pos);
}

NpcField::~NpcField() = default;

void NpcField::onEnter(Game* game)
{
	// nothing to do
}

void NpcField::onInteract(Game* game)
{
	auto iterator = game->dialogueMap.find(npcName);
	if (iterator == game->dialogueMap.end())
	{
		throw std::invalid_argument("Unknown npc name key.");
	}
	std::string currentDialogue = iterator->second;

	std::cout << TEXTBOXBORDER_UPPER_LOWER << "\n" << currentDialogue << "\n" << TEXTBOXBORDER_UPPER_LOWER << "\n";
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
